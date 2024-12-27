const std = @import("std");
const testing = std.testing;

pub fn add(a: f64, b: f64) f64 {
    std.debug.print("from zig library: n1: {}, n2: {}\n", .{ a, b });
    return a + b;
}

test "basic add functionality" {
    try testing.expect(add(1, 1) == 2);
}
