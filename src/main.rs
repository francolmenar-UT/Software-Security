use std::io;

mod bst;
use bst::BST;

use std::env;

#[derive(Debug)]
enum Command {
    Insert { age: i32, name: String },
    Erase { age: i32, name: String },
    Contains { age: i32, name: String },
    Print,
    Reset,
    Exit,
    Error(String),
}

fn parse_command(input: String) -> Command {
    let command_items: Vec<&str> = input.split_whitespace().collect();
    if command_items.len() == 0 {
        Command::Error("invalid command (empty line)".to_string())
    } else {
        match (command_items[0], command_items.len()) {
            ("p", 1) => Command::Print,
            ("q", 1) => Command::Exit,
            ("x", 1) => Command::Reset,
            ("i", 3) => {
                if let Ok(age) = command_items[1].parse::<i32>() {
                    Command::Insert {
                        age: age,
                        name: command_items[2].to_string(),
                    }
                } else {
                    Command::Error("unable to parse int (age).".to_string())
                }
            }
            ("e", 3) => {
                if let Ok(age) = command_items[1].parse::<i32>() {
                    Command::Erase {
                        age: age,
                        name: command_items[2].to_string(),
                    }
                } else {
                    Command::Error("unable to parse int (age).".to_string())
                }
            }
            ("c", 3) => {
                if let Ok(age) = command_items[1].parse::<i32>() {
                    Command::Contains {
                        age: age,
                        name: command_items[2].to_string(),
                    }
                } else {
                    Command::Error("unable to parse int (age).".to_string())
                }
            }

            (_, _) => Command::Error("invalid command.".to_string()),
        }
    }
}

fn print_fuzz_insert_erase() {
    use rand::Rng;

    let nr_iters = 100000;
    let mut bst = BST::new();

    for _ in 0..nr_iters {
        let mut rng = rand::thread_rng();

        bst.insert(rng.gen_range(0, 100000), String::from("abc"));
    }

    for _ in 0..(nr_iters / 2) {
        let mut rng = rand::thread_rng();
        bst.erase(rng.gen_range(0, 100000), String::from("abc"));
    }

    for _ in 0..nr_iters {
        let mut rng = rand::thread_rng();

        bst.insert(rng.gen_range(0, 100000), String::from("abc"));
    }

    for _ in 0..(nr_iters / 2) {
        let mut rng = rand::thread_rng();
        bst.erase(rng.gen_range(0, 100000), String::from("abc"));
    }

    bst.print_json();
}

fn main() {
    let args: Vec<String> = env::args().collect();

    // Run JSON test
    if args.len() == 2 {
        print_fuzz_insert_erase();
        return;
    }

    let mut bst = BST::new();

    loop {
        let mut input = String::new();

        match io::stdin().read_line(&mut input) {
            Ok(0) => {
                // End of file
                break;
            }
            Ok(_) => match parse_command(input) {
                Command::Insert { age, name } => {
                    bst.insert(age, name);
                }
                Command::Erase { age, name } => {
                    bst.erase(age, name);
                }
                Command::Contains { age, name } => {
                    bst.contains(age, &name);
                }
                Command::Print => {
                    bst.print_json();
                }
                Command::Reset => {
                    bst = BST::new();
                }
                Command::Exit => {
                    break;
                }
                Command::Error(error) => {
                    println!("Error: {}", error);
                }
            },
            Err(error) => println!("Error: {}", error),
        }
    }
}
