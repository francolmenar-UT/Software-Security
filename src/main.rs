use std::io;

mod bst;
use bst::BST;

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

fn main() {
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
