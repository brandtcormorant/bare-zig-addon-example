const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const target_os = target.result.os.tag;
    const is_windows = target_os == .windows;
  
    const obj = b.addObject(.{
        .name = "bare_zig_example",
        .root_source_file = b.path("src/c_api.zig"),
        .target = target,
        .optimize = optimize,
        .pic = true,
    });

    if (is_windows and (optimize == .Debug or optimize == .ReleaseSafe)) {
        obj.bundle_compiler_rt = true;
    }
    
    if (is_windows) {
        obj.linkSystemLibrary("ntdll");
    }

    const obj_ext = if (is_windows) ".obj" else ".o";
    const obj_path = obj.getEmittedBin();
    const install_obj = b.addInstallFile(
        obj_path,
        b.fmt("lib/bare_zig_example{s}", .{obj_ext}),
    );

    b.getInstallStep().dependOn(&install_obj.step);
        
    const lib_unit_tests = b.addTest(.{
        .root_source_file = b.path("src/root.zig"),
        .target = target,
        .optimize = optimize,
    });

    const run_lib_unit_tests = b.addRunArtifact(lib_unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_lib_unit_tests.step);
}
