#ifndef STATUS_H
#define STATUS_H
enum class Status: int {
    SUCCESS,
    CYL_PARSE_ERROR,
    PARAM_TYPE_MISMATCH,
    PARAM_UNKNOWN
};
#endif
