const std = @import("std");
const example = @import("root.zig");

export fn bare_zig_add(a: f64, b: f64) callconv(.C) f64 {
    std.debug.print("from zig c api export: n1: {}, n2: {}\n", .{ a, b });
    return example.add(a, b);
}
