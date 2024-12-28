const std = @import("std");

export fn bare_zig_add(a: f64, b: f64) f64 {
    const sum = a + b;
    std.debug.print("from zig: n1: {} + n2 {} = {}", .{ a, b, sum });
    return a + b;
}
