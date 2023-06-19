#![warn(clippy::all, clippy::pedantic, clippy::nursery)]

mod bitvec;
mod args;

use std::env;

use crate::bitvec::ExpandableBitVec;
use args::Args;
use owo_colors::OwoColorize;
use regex::Regex;

fn main () {
    if let Err(e) = main_inner() {
        eprintln!("\nFailed: {e:?}");
    }
}

fn main_inner() -> Result<(), Box<dyn std::error::Error>> {
    
    let Args {file_contents: contents, pattern} = Args::try_from(env::args().skip(1).collect::<Vec<String>>())?;

    let re = Regex::new(&pattern)?;

    let mut bv = ExpandableBitVec::new(256);
    for line in contents.lines() {
        let size = line.len();
        bv.extend_to_size(size);

        for m in re.find_iter(line) {
            for index in m.range() {
                bv.set(index, true);
            }
        }

        for (col, char) in line.chars().enumerate() {
            if bv.index(col) {
                print!("{}", char.green());
            } else {
                print!("{char}");
            }
        }

        bv.clear();
        println!();
    }

    Ok(())
}
