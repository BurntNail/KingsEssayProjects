const std = @import("std");
const ebv = @import("expandablebitvec.zig");

const BUFFER_SIZE: usize = 1024; //A whole kibibyte max?!?!?! shocking

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    if (args.len == 1) {
        std.debug.print("You need to pass in a file as the first argument.\n", .{});
        return;
    } else if (args.len == 2) {
        std.debug.print("You need to pass in a pattern to look for as the second argument.\n", .{});
        return;
    }

    const filename = args[1];
    // const pattern = args[2];

    const file = try std.fs.cwd().openFile(filename, .{});
    try file.seekTo(0);
    defer file.close();

    // // var file_contents = std.ArrayList(u8).init(allocator);
    // // defer file_contents.deinit();

    // var buf_reader = std.io.bufferedReader(file.reader());
    // var in_stream = buf_reader.reader();
    // var buf: [BUFFER_SIZE]u8 = undefined;

    // const contents = try file.reader().readAllAlloc(
    //     allocator,
    //     BUFFER_SIZE,
    // );
    // defer allocator.free(contents);

    // var buffer = [_]u8{0} ** BUFFER_SIZE;

    // while (try file.reader().readUntilDelimiterOrEof(&buffer, '\n')) |line| {
    //     std.debug.print("Found Line: {s}\n", .{line[..]});
    // }

    var local_ebv = ebv.ExpandableBitVec.new();
    std.debug.print("Var: {d}\n", .{local_ebv.abc()});
}
