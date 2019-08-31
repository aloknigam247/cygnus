############################################################
# Commonn functions for logging and command line parsing   #
############################################################

################################ 
# Wrapper for exit             #
# Usage: EXIT <return-code>    #
################################
declare EXITCODE=0
EXIT(){
    exit $EXITCODE
}

############################
# Log wrapper              #
# Usage: Log <tag> "<msg>" #
############################
LOG(){
    local msg=${2:?"message missing."}
    case $1 in
        E)
            echo "[ERROR] $msg"
            EXITCODE=1
            ;;
        I)
            echo "[INFO] $msg"
            ;;
        W)
            echo "[WARN] $msg"
            ;;
        *)
            LOG E "unrecognized log type"
            EXIT
            ;;
    esac
}

####################################################################
# How to create new option                                         #
#   * help      : create help statement, use . in place of space   #
#   * metavar   : string to be displayed for option argument       #
#   * value     : type of value                                    #
#                   bool    - no argument                          #
#                   string  - option expects single argument       #
#   * with      : mention dependency of option                     #
#   ** POS      : special option to provide positional args        #
#                                                                  #
#   OPTION['option-name']="list of above options"                  #
#   OPTION['POS']="variable-name"                                  #
####################################################################
declare -A OPTION
declare -A VALUES
declare POS_NAME

# Default options
OPTION['-h']='value=bool help=print.help'
OPTION['--help']='value=bool help=print.help'

# Print usage
usage(){
    # scan all options for alignments
    max_len=0
    pos_name=''
    for opt in ${!OPTION[@]}; do
        for param in ${OPTION[$opt]}; do
            case $param in
                metavar=*)
                    len=${param#*=}
                    t_len=$(( ${#opt} + ${#len} ))
                    [[ $max_len < $t_len ]] && max_len=$t_len
                    break
                    ;;
                count=1)
                    pos_name="$POS_NAME"
                    break
                    ;;
                count=0+)
                    pos_name="[$POS_NAME...]"
                    break
                    ;;
                count=1+)
                    pos_name="$POS_NAME..."
                    break
                    ;;
            esac
        done
        [[ $max_len < ${#opt} ]] && max_len=${#opt}
    done

    # print usage now
    echo "Usage: `basename $0` [option] $pos_name"
    for opt in `echo ${!OPTION[@]} | sed 's/ /\n/g' | sort | grep -v POS`; do
        m=''
        h=''
        mst=''
        for param in ${OPTION[$opt]}; do
            case $param in
                metavar=*)
                    m="<${param#*=}>"
                    ;;
                help=*)
                    h=${param#*=}
                    ;;
                with=*)
                    mst=", depends on ${param#*=}"
                    ;;
            esac
        done
        printf "    %-$(($max_len + 3))s: %s%s\n" "$opt $m" "${h//./ }" "$mst"
    done
    EXIT
}

# Error message for option
# Usage: optionError <option>
optionError(){
    LOG E "option \`$1' expects argument"
    for param in ${option[$1]};do
        case $param in
            metavar=*)
                m="<${param#*=}>"
                ;;
            help=*)
                h=${param#*=}
                ;;
            with=*)
                mst=", depends on ${param#*=}"
                ;;
        esac
    done
    if [[ -z $h ]]; then
        LOG W "short help for option \`$1' is missing."
    else
            echo "    $1 $m: ${h//./ } $mst"
    fi
}

# Command line parser
# It uses global variable OPTION and VALUES
#   OPTION: associative array that has all options defined
#   VALUES: values of options mentioned in OPTION
parseCmdLine() {
    declare -A must

    # Set positional argument name
    if [[ ${OPTION['POS']} ]]; then
        for param in ${OPTION['POS']}; do
            case $param in
                dest=*)
                    POS_NAME=${param#*=}
                    break
                    ;;
            esac
        done
    fi

    while [ $1 ]; do
        opt=$1
        dest=''
        val=''
        error=''
        if [[ ${OPTION[$opt]} ]]; then
            for param in ${OPTION[$opt]}; do
                case $param in
                    value=*)
                        if [[ $param == "value=string" ]]; then
                            if [[ -n $2 && ! $2 =~ ^- ]]; then
                                val=$2
                                shift
                            else
                                optionError $opt
                                error=1
                                continue
                            fi
                        elif [[ $param == "value=bool" ]]; then # can be removed
                            val="true"
                        fi
                        ;;
                    with=*)
                        local deps=${param#*=}
                        for o in ${deps//,/ }; do
                            must["$o"]=$opt
                        done
                        ;;
                    metavar=*|help=*)
                        ;;
                    *)
                        LOG W "invalid parameter $param defined in option \`$opt'"
                        error=1
                        continue
                        ;;
                esac
            done
            if [[ $val ]]; then
                VALUES[$opt]=$val
            fi
        elif [[ $1 =~ ^- ]]; then
            LOG I "ignoring unknown option \`$opt'"
        else
            pos+=" $opt"
        fi
        shift
    done
    if [[ -n $pos ]]; then
        VALUES[$POS_NAME]="$pos"
        echo ""
    fi

    if [[ ${VALUES["-h"]} || ${VALUES["--help"]} ]]; then
        usage
    fi

    for o in ${!must[@]}; do
        if [[ -z ${VALUES[$o]} ]]; then
            LOG E "option\[s\] $o is missing needed by ${must[$o]}"
            optionError ${must[$o]}
        fi
    done

    for i in ${!VALUES[@]}; do
        echo "$i: ${VALUES[$i]}"
    done
}
