############################################################
# Commonn functions for logging and command line parsing   #
# NOTE: all variable name start with _ in this file        #
############################################################

################################ 
# Wrapper for exit             #
# Usage: EXIT <return-code>    #
################################
declare _EXITCODE=0
EXIT(){
    exit ${1:-$_EXITCODE}
}

############################
# Log wrapper              #
# Usage: Log <tag> "<msg>" #
############################
LOG(){
    local _msg=${2:?"message missing."}
    case $1 in
        E)
            echo "|ERROR| $_msg"
            _EXITCODE=1
            ;;
        I)
            echo "|INFO| $_msg"
            ;;
        W)
            echo "|WARN| $_msg"
            ;;
        *)
            LOG E "unrecognized log type"
            EXIT 1
            ;;
    esac
}

#####################################################################
# How to create new option                                          #
#   * eval:     : action to evaluate when option is found           #
#   * help:     : create help statement, use . in place of space    #
#   * metavar:  : string to be displayed for option argument        #
#   * value:    : type of value                                     #
#                  bool    - no argument                            #
#               : string  - option expects single argument          #
#   * with:     : mention dependency of option                      #
#   ** POS      : special option to provide positional args         #
#                                                                   #
#   OPTION['option-name']="list of above options"                   #
#   OPTION['POS']="variable-name"                                   #
#####################################################################
declare -A OPTION
declare -A VALUES
declare _POS_NAME

# Default options
OPTION['-h']='value:bool,help:print help'
OPTION['--help']='value:bool,help:print help'

# Print usage
usage(){
    # scan all options for alignments
    local _max_len=0
    local _pos_name=''
    for _opt in ${!OPTION[@]}; do
        local _IFS_Prev=$IFS
        IFS=','
        for _param in ${OPTION[$_opt]}; do
            case $_param in
                metavar:*)
                    len=${_param#*:}
                    t_len=$(( ${#_opt} + ${#_len} ))
                    [[ $_max_len -lt $t_len ]] && _max_len=$t_len
                    break
                    ;;
                count:1)
                    _pos_name="$_POS_NAME"
                    break
                    ;;
                count:0+)
                    _pos_name="[$_POS_NAME...]"
                    break
                    ;;
                count:1+)
                    _pos_name="$_POS_NAME..."
                    break
                    ;;
            esac
        done
        [[ $_max_len -lt ${#_opt} ]] && _max_len=${#_opt}
        IFS=$_IFS_Prev
    done

    # print usage now
    echo "Usage: `basename $0` [options] $_pos_name"
    for opt in `echo ${!OPTION[@]} | sed 's/ /\n/g' | sort | grep -v POS`; do
        _meta=''
        _help=''
        _with=''
        _without=''
        local IFS_Prev=$IFS
        IFS=','
        for param in ${OPTION[$opt]}; do
            case $param in
                metavar:*)
                    _meta="<${param#*:}>"
                    ;;
                help:*)
                    _help=${param#*:}
                    ;;
                with:*)
                    _with=", with ${param#*:}"
                    ;;
                without:*)
                    _without=", without ${param#*:}"
                    ;;
            esac
        done
        IFS=$IFS_Prev
        printf "    %-$(($_max_len + 3))s: %s%s%s\n" "$opt $_meta" "${_help}" "$_with" "$_without"
    done
    EXIT
}

# Error message for option
# Usage: optionError <option>
optionError(){
    LOG E "option \`$1' expects argument"
    local _IFS_Prev=$IFS
    local _meta=''
    local _help=''
    local _with=''
    local _without=''
    IFS=','
    for _param in ${OPTION[$1]};do
        case $_param in
            metavar:*)
                _meta="<${_param#*:}>"
                ;;
            help:*)
                _help=${_param#*:}
                ;;
            with:*)
                _with=", with ${_param#*:}"
                ;;
            _without:*)
                _without=", without ${_param#*:}"
        esac
    done
    IFS=$_IFS_Prev
    if [[ -z $_help ]]; then
        LOG W "short help for option \`$1' is missing."
    else
            echo "    $1 $_meta: ${_help//./ } $_with $_without"
    fi
}

# Command line parser
# It uses global variable OPTION and VALUES
#   OPTION: associative array that has all options defined
#   VALUES: values of options mentioned in OPTION
parseCmdLine() {
    declare -A _with
    declare -A _without

    # Set positional argument name
    local _IFS_Prev=$IFS
    IFS=','
    if [[ ${OPTION['POS']} ]]; then
        for _param in ${OPTION['POS']}; do
            case $_param in
                dest:*)
                    _POS_NAME=${_param#*:}
                    break
                    ;;
            esac
        done
    fi
    IFS=$_IFS_Prev

    while [ $1 ]; do
        _opt=$1
        _val=''
        _error=''
        if [[ ${OPTION[$_opt]} ]]; then
            local _IFS_Prev=$IFS
            IFS=','
            for _param in ${OPTION[$_opt]}; do
                _dest=$_opt
                case $_param in
                    dest:*)
                        _dest=${_param#*:}
                        ;;
                    eval:*)
                        eval ${_param#*:}
                        ;;
                    value:*)
                        if [[ $_param == "value:string" ]]; then
                            if [[ -n $2 && ! $2 =~ ^- ]]; then
                                _val=$2
                                shift
                            else
                                optionError $_opt
                                _error=1
                                continue
                            fi
                        elif [[ $_param == "value:bool" ]]; then # can be removed
                            _val="true"
                        fi
                        ;;
                    with:*)
                        _deps=${_param#*:}
                        for _o in ${_deps//,/ }; do
                            _with["$_o"]=$_opt
                        done
                        ;;
                    without:*)
                        _deps==${_param#*:}
                        for _o in ${_deps//,/ }; do
                            _without["$_o"]=$_opt
                        done
                        ;;
                    metavar:*|help:*)
                        ;;
                    *)
                        LOG W "invalid parameter $_param defined in option \`$_opt'"
                        _error=1
                        continue
                        ;;
                esac
            done
            IFS=$_IFS_Prev
            if [[ $_val ]]; then
                VALUES[$_dest]=$_val
            fi
        elif [[ $1 =~ ^- ]]; then
            LOG I "ignoring unknown option \`$_opt'"
        else
            _pos+=" $_opt"
        fi
        shift
    done
    if [[ -n $_pos && -n $_POS_NAME ]]; then
        VALUES[$_POS_NAME]="$_pos"
        echo ""
    fi

    if [[ ${VALUES["-h"]} || ${VALUES["--help"]} ]]; then
        usage
    fi

    for _o in ${!_with[@]}; do
        if [[ -z ${VALUES[$_o]} ]]; then
            LOG E "option\[s\] $_o is missing needed by ${_with[$_o]}"
            optionError ${_with[$_o]}
        fi
    done
    
    for _o in ${!_without[@]}; do
        if [[ ${VALUES[$_o]} ]]; then
            LOG E "can not combine $_o with ${_without[$_o]}"
            optionError ${_without[$_o]}
        fi
    done
    
    [[ $_EXITCODE -ne 0 ]] && EXIT

    echo "Options: "
    for _i in ${!VALUES[@]}; do
        echo -e "    $_i: ${VALUES[$_i]}"
    done
}
