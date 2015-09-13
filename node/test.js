var fs = require("fs");
var t = require("./grunner");
var result = t.run({
    path: "/Users/geminiwen/Code/CLionProjects/grunner/test/test",
    fin: fs.openSync("/Users/geminiwen/Code/CLionProjects/grunner/test/test.in", "r"),
    fout: fs.openSync("/Users/geminiwen/Code/CLionProjects/grunner/test/test.out", "w"),
    timeLimit: 1000,
    memoryLimit: 1024 * 64,
    uid: process.getuid()
});

console.log("result in node:" + result);
