#pragma once

#include <stdio.h>

#define STYLE_DEFAULT   "\033[0m"
#define STYLE_ERROR     "\033[31;1m"
#define STYLE_OK        "\033[32;1m"

#define STR_FMT_ERROR(str)   STYLE_ERROR str STYLE_DEFAULT
#define STR_FMT_OK(str)      STYLE_OK str STYLE_DEFAULT