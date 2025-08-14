// #include "files/LgsFile.h"
// #include "logos/LgsApp.h"
// #include "logos/LgsModule.h"
//
// #include <doctest.h>
// #include <regex>
//
// typedef map<string, map<string, std::vector<string>>> ExpectedInstructions;
//
// string normalize(const string& str) {
//     const auto newStr = regex_replace(str, regex(R"(, align \d+)"), "");
//     const auto start = find_if_not(newStr.begin(), newStr.end(), ::isspace);
//     const auto end = find_if_not(newStr.rbegin(), newStr.rend(), ::isspace).base();
//     if (start >= end) return "";
//     return string(start, end);
// }
//
// void compareCode(const string& codeText, ExpectedInstructions expected) {
//     LgsApp app;
//     app.parseSrcFile(codeText);
//     CHECK(app.analyse());
//     const auto module = app.files[0]->generateIR();
//     const auto IRModule = module->IRModule;
//     for (auto& func : IRModule->functions()) {
//         auto expectedBlocks = expected[func.getName().str()];
//         CHECK_EQ(func.size(), expectedBlocks.size());
//         for (auto& bb : func) {
//             const auto expectedInsts = expectedBlocks[bb.getName().str()];
//             CHECK_EQ(bb.size(), expectedInsts.size());
//             auto i = 0;
//             for (auto& inst : bb) {
//                 string irString;
//                 raw_string_ostream stream(irString);
//                 inst.print(stream);
//                 stream.flush();
//                 const auto actualInst = normalize(irString);
//                 CHECK_EQ(expectedInsts[i], actualInst);
//                 i++;
//             }
//         }
//     }
// }
//
// TEST_CASE("CodegenTestAddition") {
//     const auto codeText = R"(
//         main() {
//             a = 2
//             b = 4
//             c = a + b
//         }
//     )";
//     const map<string, map<string, std::vector<string>>> expectedInts = {
//         {"main", {
//             {"entry", {
//                 "%0 = alloca i32",
//                 "store i32 2, ptr %0",
//                 "%1 = alloca i32",
//                 "store i32 4, ptr %1",
//                 "%2 = load i32, ptr %0",
//                 "%3 = load i32, ptr %1",
//                 "%4 = add i32 %2, %3",
//                 "%5 = alloca i32",
//                 "store i32 %4, ptr %5",
//                 "ret i32 0",
//             }}
//         }}
//     };
//     compareCode(codeText, expectedInts);
// }
//
// TEST_CASE("CodegenTestIfStmt") {
//     const auto codeText = R"(
//     func(x: Int) {
//         if x > 0 {
//             a = 2
//         }
//     }
//
//     main() {
//         func(10)
//     }
//     )";
//     const map<string, map<string, std::vector<string>>> expectedInts = {
//         {"main", {
//             {"entry", {
//                 "call void @func(i32 10)",
//                 "ret i32 0",
//             }}}
//         },
//         {"func", {
//             {"entry", {
//                 "%0 = icmp sgt i32 %x, 0",
//                 "br i1 %0, label %if_true, label %if_end",
//             }},
//             {"if_true", {
//                 "%1 = alloca i32",
//                 "store i32 2, ptr %1", "br label %if_end",
//             }},
//             {"if_end", {
//                 "ret void",
//             }},
//         },
//     }};
//     compareCode(codeText, expectedInts);
// }
