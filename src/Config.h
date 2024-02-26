#pragma once
#include "Global.h"

std::string defaultConfig = R"({
    "ChatFormat": "[%chatformatter_dimension%] {player} >> {message}",
    "DimensionNameMap": {
        "Overworld": "Overworld",
        "Nether": "Nether",
        "TheEnd": "The End"
    }
})";