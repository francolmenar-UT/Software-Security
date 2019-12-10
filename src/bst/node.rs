use std::cmp;

pub type NodePtr = Box<Node>;
pub type Link = Option<NodePtr>;

pub struct Node {
    key: i32,
    data: String,
    left: Link,
    right: Link,
    height: i32,
}

fn rotate_right(mut node: NodePtr) -> NodePtr {
    let mut new_root = node.left.take().expect("rotate_right()");
    node.left = new_root.right.take();
    node.update_height();

    new_root.right = Some(node);
    new_root.update_height();

    new_root
}

fn rotate_left(mut node: NodePtr) -> NodePtr {
    let mut new_root = node.right.take().expect("rotate_left()");
    node.right = new_root.left.take();
    node.update_height();
    new_root.left = Some(node);
    new_root.update_height();

    new_root
}

impl Node {
    pub fn new_leaf(value: i32, data: String) -> Self {
        Node {
            key: value,
            data: data,
            left: None,
            right: None,
            height: 1,
        }
    }

    pub fn balance(&self) -> i32 {
        Node::height(&self.left) - Node::height(&self.right)
    }

    fn insert_helper(node: Link, key: i32, data: String) -> Link {
        return Some(match node {
            Some(n) => Node::insert(n, key, data),
            None => Box::new(Node::new_leaf(key, data)),
        });
    }

    pub fn insert(mut root: NodePtr, key: i32, data: String) -> NodePtr {
        if key > root.key {
            root.right = Node::insert_helper(root.right.take(), key, data);
        } else if key < root.key {
            root.left = Node::insert_helper(root.left.take(), key, data);
        }

        Node::update_height(&mut *root);
        Node::reconstruct(root)
    }

    fn find_min_sub_node(root: &Link) -> Option<&NodePtr> {
        let mut tmp: &Link = root;

        loop {
            match &tmp.as_ref() {
                Some(node) => {
                    if node.left.is_none() {
                        return tmp.as_ref();
                    } else {
                        tmp = &node.left;
                    }
                }
                None => unreachable!(),
            }
        }
    }

    pub fn erase(mut root: Link, key: i32, data: String) -> Link {
        match root.take() {
            None => return None,
            Some(mut node) => {
                if key < node.key {
                    node.left = Node::erase(node.left, key, data);
                } else if key > node.key {
                    node.right = Node::erase(node.right, key, data);
                } else if key == node.key && data == node.data {
                    if node.left.is_none() || node.right.is_none() {
                        let mut tmp: Link;

                        if node.left.is_none() {
                            tmp = node.left.take();
                        } else {
                            tmp = node.right.take();
                        }

                        match tmp.take() {
                            None => unreachable!(),
                            Some(n) => {
                                node.data = n.data;
                                node.key = n.key;
                            }
                        }
                    } else {
                        let mut tmp = Node::find_min_sub_node(&node.right);

                        match tmp.take() {
                            None => unreachable!(),
                            Some(n) => {
                                node.key = n.key;
                                node.data = n.data.clone();
                            }
                        }

                        node.right = Node::erase(node.right, node.key, node.data.clone());
                    }
                } else {
                    return root;
                }

                root = Some(node);
            }
        }

        if root.is_none() {
            return None;
        }

        root.map(|mut n| {
            Node::update_height(&mut n);
            Node::reconstruct(n)
        })
    }

    fn key(node: &Link) -> i32 {
        match node {
            Some(node) => node.key,
            None => unreachable!(),
        }
    }

    fn rotate_left_successor(mut root: NodePtr) -> NodePtr {
        let target = root.left.unwrap();
        if Node::height(&target.left) < Node::height(&target.right) {
            root.left = Some(rotate_left(target));
            Node::update_height(&mut root);
        } else {
            root.left = Some(target);
        }
        rotate_right(root)
    }

    fn rotate_right_successor(mut root: NodePtr) -> NodePtr {
        let target = root.right.unwrap();

        if Node::height(&target.left) > Node::height(&target.right) {
            root.right = Some(rotate_right(target));
            Node::update_height(&mut root);
        } else {
            root.right = Some(target)
        }
        rotate_left(root)
    }

    fn reconstruct(mut root: NodePtr) -> NodePtr {
        let height_diff = Node::balance(&root);
        if height_diff > 1 {
            return Node::rotate_left_successor(root);
        }

        if height_diff < -1 {
            return Node::rotate_right_successor(root);
        }

        Node::update_height(&mut *root);

        root
    }

    pub fn contains(&self, key: i32, data: &String) -> bool {
        if key > self.key {
            return match &self.right {
                None => return false,
                Some(node) => node.contains(key, data),
            };
        } else if key < self.key {
            return match &self.left {
                None => return false,
                Some(node) => node.contains(key, data),
            };
        } else if data == &self.data {
            return true;
        } else {
            return false;
        }
    }

    fn update_height(&mut self) {
        self.height = cmp::max(Node::height(&self.right), Node::height(&self.left)) + 1;
    }

    pub fn height(node: &Link) -> i32 {
        node.as_ref().map_or(0, |n| n.height)
    }

    pub fn inorder_print(&self) {
        match self.left {
            Some(ref node) => {
                node.inorder_print();
            }
            None => (),
        }

        print!("{{ \"{}\", \"{}\" }}, ", self.key, self.data);

        match self.right {
            Some(ref node) => {
                node.inorder_print();
            }
            None => (),
        }
    }

    pub fn print_json(&self) {
        print!("[");
        print!("{{ \"{}\": \"{}\" }}, ", self.key, self.data);
        match self.left {
            Some(ref node) => {
                node.print_json();
            }
            None => {
                print!("null");
            }
        }
        print!(", ");

        match self.right {
            Some(ref node) => {
                node.print_json();
            }
            None => {
                print!("null");
            }
        }

        print!("]");
    }

    pub fn debug_print(&self) {
        print!("[");
        print!("{{ key={}, h={} }}, ", self.key, self.height);
        match self.left {
            Some(ref node) => {
                node.debug_print();
            }
            None => {
                print!("null");
            }
        }
        print!(", ");

        match self.right {
            Some(ref node) => {
                node.debug_print();
            }
            None => {
                print!("null");
            }
        }

        print!("]");
    }
}
