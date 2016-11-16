import qbs

CppApplication {
    consoleApplication: true
    cpp.cxxFlags: "-std=c++11"
    files: [
        "main.cpp",
        "analyze.h",
        "analyze.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
