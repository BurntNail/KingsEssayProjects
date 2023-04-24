const std = @import("std");

//https://zig.news/xq/zig-build-explained-part-2-1850

// const pkgs = struct {
//     const ebv = std.build.Pkg{
//         .name = "ebv",
//         .source = .{ .path = "src/expandablebitvec.zig" },
//         .dependencies = &[_]std.build.Pkg{},
//     };
// };

pub fn build(b: *std.build.Builder) void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard release options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall.
    const mode = b.standardReleaseOptions();

    const mandlebrot_exe = b.addExecutable("ZigMandlebrot", "src/mandlebrot.zig");
    // mandlebrot_exe.addPackage(pkgs.ebv);
    mandlebrot_exe.setTarget(target);
    mandlebrot_exe.setBuildMode(mode);
    mandlebrot_exe.install();

    const mandlebrot_run_cmd = mandlebrot_exe.run();
    mandlebrot_run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        mandlebrot_run_cmd.addArgs(args);
    }

    const mandlebrot_run_step = b.step("mandlebrot", "Run Mandlebrot");
    mandlebrot_run_step.dependOn(&mandlebrot_run_cmd.step);

    const minigrep_exe = b.addExecutable("ZigMinigrep", "src/minigrep.zig");
    // minigrep_exe.add
    minigrep_exe.setTarget(target);
    minigrep_exe.setBuildMode(mode);
    minigrep_exe.install();

    const minigrep_run_cmd = minigrep_exe.run();
    minigrep_run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        minigrep_run_cmd.addArgs(args);
    }

    const minigrep_run_step = b.step("minigrep", "Run Minigrep");
    minigrep_run_step.dependOn(&minigrep_run_cmd.step);

    // const exe_tests = b.addTest("src/main.zig");
    // exe_tests.setTarget(target);
    // exe_tests.setBuildMode(mode);

    // const test_step = b.step("test", "Run unit tests");
    // test_step.dependOn(&exe_tests.step);
}
