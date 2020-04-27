mod node;
use node::Link;
use node::Node;

pub struct SortedContainer {
    root: Link,
}

impl SortedContainer {
    pub fn new() -> Self {
        return SortedContainer { root: None };
    }

    pub fn insert(&mut self, key: i32, data: String) {
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

    pub fn contains(&self, key: i32, data: &String) -> bool {
        match self.root {
            Some(ref node) => node.contains(key, data),
            None => false,
        }
    }

    // Used for debugging
    #[allow(dead_code)]
    pub fn inorder_print(&self) {
        match self.root {
            Some(ref node) => {
                node.inorder_print();
                println!("");
            }
            None => println!("None"),
        };
    }

    pub fn print(&self) {
        match self.root {
            Some(ref node) => {
                node.print();
                println!("");
            }
            None => println!("null"),
        };
    }

    #[allow(dead_code)]
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
    use super::SortedContainer;
    #[test]
    fn basics() {
        let mut bst = SortedContainer::new();

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
        let mut bst = SortedContainer::new();

        for _ in 0..nr_iters {
            let mut rng = rand::thread_rng();

            bst.insert(rng.gen_range(0, 1000), String::from("abc"));
            bst.print();
        }
    }

    #[test]
    fn print_fuzz_insert_erase() {
        use rand::Rng;

        let nr_iters = 10000;
        let mut bst = SortedContainer::new();

        for _ in 0..nr_iters {
            let mut rng = rand::thread_rng();
            bst.insert(rng.gen_range(0, 10000), String::from("abc"));
        }

        for _ in 0..(nr_iters / 2) {
            let mut rng = rand::thread_rng();
            bst.erase(rng.gen_range(0, 10000), String::from("abc"));
        }

        bst.print();
    }
}
