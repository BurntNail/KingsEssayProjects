pub const ExpandableBitVec = struct {
    backing: [100]u32,

    pub fn new () ExpandableBitVec {
        return ExpandableBitVec {
            .backing = [_]u32{0} ** 100
        };
    }

    pub fn abc (self: *ExpandableBitVec) i32 {
        return self.backing.len;
    }
};
