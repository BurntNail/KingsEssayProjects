const std = @import("std");

const ASCII = " .:;+=xX$&";
const ASCII_LEN_MINUX_ONE: usize = 9;

const WIDTH: usize = 50;
const HEIGHT: usize = 35;

const WIDTH_X_HEIGHT: usize = WIDTH * HEIGHT;

const RE_START: f32 = -2.0;
const RE_END: f32 = 1.0;
const IM_START: f32 = -1.0;
const IM_END: f32 = 1.0;

const MAX_ITERS: u8 = 50;

pub fn main() !void {
    // var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    // defer _ = gpa.deinit();
    // const allocator = gpa.allocator();

    var iters = [_]u8{0} ** (WIDTH_X_HEIGHT);

    // var x: f32 = 0.0;
    // var y: f32 = 0.0;

    // while (y < HEIGHT) : (y += 1.0) {
    //     while (x < WIDTH) : (x += 1.0) {

    //     }
    // } TODO: check speed of this vs below

    for ([_]u8{0} ** HEIGHT) |_, y| {
        for ([_]u8{0} ** WIDTH) |_, x| {
            const real = (@intToFloat(f32, x) / @as(f32, WIDTH)) * (RE_END - RE_START) + RE_START;
            const imaginary = (@intToFloat(f32, y) / @as(f32, HEIGHT)) * (IM_END - IM_START) + IM_START;

            var re: f32 = 0.0;
            var im: f32 = 0.0;
            var iter: u8 = 0.0;

            while (re * re + im * im < 4.0 and iter < MAX_ITERS) {
                re = re * re - im * im + real;
                im = re * im + re * im + imaginary;
                iter += 1;
            }

            iters[y * WIDTH + x] = iter;
        }
    }

    var max: u8 = 0;
    var min: u8 = MAX_ITERS;

    for (iters) |iter| {
        if (iter < MAX_ITERS and iter > max) {
            max = iter;
        } else if (iter < min) {
            min = iter;
        }
    }

    const diff: f32 = @intToFloat(f32, max - min);

    var string = [_]u8{0} ** ((WIDTH + 1) * HEIGHT + 1);
    var row_pos: usize = 0;
    var string_i: usize = 0;
    for (iters) |iter| {
        if (iter == MAX_ITERS) {
            string[string_i] = ASCII[ASCII_LEN_MINUX_ONE];
        } else {
            const mapped = iter - min;
            const pos = @intToFloat(f32, mapped) / diff;
            string[string_i] = ASCII[@floatToInt(usize, pos * @as(f32, ASCII_LEN_MINUX_ONE))];
        }

        string_i += 1;

        row_pos += 1;
        if (row_pos == WIDTH) {
            row_pos = 0;
            string[string_i] = '\n';
            string_i += 1;
        }
    }

    std.debug.print("{s}", .{string});
}
