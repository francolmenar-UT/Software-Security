mod node;
use node::Link;
use node::Node;

pub struct BST {
    root: Link,
}

impl BST {
    pub fn new() -> Self {
        return BST { root: None };
    }

    pub fn insert(&mut self, key: i32, data: String) {
        if self.contains(key, &data) {
            return;
        }

        match self.root.take() {
            Some(node) => self.root = Some(Node::insert(node, key, data)),
            None => self.root = Some(Box::new(Node::new_leaf(key, data))),
        };
    }

    pub fn erase(&mut self, key: i32, data: String) {
        if !self.contains(key, &data) {
            return;
        }

        match self.root.take() {
            Some(node) => self.root = Node::erase(Some(node), key, data),
            // Should be caught by the contains
            None => unreachable!(),
        }
    }

    pub fn height(&self) -> i32 {
        Node::height(&self.root)
    }

    pub fn contains(&self, key: i32, data: &String) -> bool {
        match self.root {
            Some(ref node) => node.contains(key, data),
            None => false,
        }
    }

    pub fn inorder_print(&self) {
        match self.root {
            Some(ref node) => {
                node.inorder_print();
                println!("");
            }
            None => println!("None"),
        };
    }

    pub fn print_json(&self) {
        match self.root {
            Some(ref node) => {
                node.print_json();
                println!("");
            }
            None => println!("null"),
        };
    }

    pub fn debug_print(&self) {
        match self.root {
            Some(ref node) => {
                node.debug_print();
                println!("");
            }
            None => println!("null"),
        }
    }
}

extern crate rand;

#[cfg(test)]
mod test {
    use super::BST;
    #[test]
    fn basics() {
        let mut bst = BST::new();

        let s = String::from("Alex");

        assert_eq!(bst.contains(123, &s), false);
        assert_eq!(bst.contains(1337, &s), false);

        bst.insert(123, String::from("Alex"));

        assert_eq!(bst.contains(123, &s), true);
        assert_eq!(bst.contains(1337, &s), false);

        for x in 0..100 {
            bst.insert(x, String::from("hejsan"));
        }

        for x in 0..100 {
            assert_eq!(bst.contains(x, &String::from("hejsan")), true);
        }
    }

    #[test]
    fn print_fuzz_insert() {
        use rand::Rng;

        let nr_iters = 100;

        for _ in 0..nr_iters {
            let mut rng = rand::thread_rng();
            let mut bst = BST::new();

            bst.insert(rng.gen_range(0, 1000), String::from("abc"));
            bst.print_json();
        }
    }
}
