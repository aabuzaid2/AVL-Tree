#include"Header.h"



node::node() {			//constructor
	right = NULL;
	left = NULL;
	height = 0;
	key = "x";
}

bool tree::search(string key) {				//returns true or false and only takes the key you would like to find
	if (root == NULL) return false;
	else
		if (key == root->key) return true;
		else
			if (key > root->key) {
				if (searchn(root->right, key)) return true;
				else return false;
			}
			else {
				if (searchn(root->left, key))
					return true;
				else return false;
			}
}

bool tree::searchn(node* nroot, string key) {		//returns true or false but takes a pointer to the node you want to start with
	if (nroot == NULL) return false;
	else
		if (key == root->key) return true;
		else 
			if (key > root->key) {
				if (searchn(root->right, key))
					return true;
				else return false;
			}
			else {
				if (searchn(root->left, key))
					return true;
				else return false;
			}
}

node* tree::searchp(node* rt, string key, node* parent) {			//returns a pointer to the node and its parent
	node* s;
	node* x;
	if (rt == NULL) return NULL;
	else
		if (key == rt->key) {
			return rt;
		}
		else {
			if (key > rt->key) {
				s = rt->right;
				parent = rt;
				x = searchp(s, key, parent);
			}
			else {
				s = rt->left;
				parent = rt;
				x = searchp(s, key, parent);
			}
			return x;
		}
}

bool tree::insert(string x) {	
	if (search(x)) {
		return false;
	}
	else {
		if (root == NULL) {
			node* newn = new node;
			newn->key = x;
			return true;
		}
		else {
			if (x > root->key) {
				if (root->right == NULL) {
					root->right = new node;
					root->right->key = x;
					root->height += 1;
					checkbal(x);
					return true;
				}
				else {
					findplace(x, root->right);		//fix
					return true;
				}
			}
			else {
				if (root->left == NULL) {
					root->left = new node;
					root->left->key = x;
					root->height += 1;
					checkbal(x);
					return true;
				}
				else {
					findplace(x, root->left);		//fix
					return true;
				}
			}
		}
	}

}

void tree::findplace(string key, node* rt) {		
	bool p = false;
	node* par = NULL;
	while (p == false) {
		if (key > rt->key) {
			if (rt->right == NULL) {
				rt->right = new node;
				rt->right->key = key;
				rt->height += 1;
				checkbal(key);
				p = true;
			}
			else {
				par = rt;
				rt = rt->right;
			}
		}
		else {
			if (rt->left == NULL) {
				rt->left = new node;
				rt->left->key = key;
				rt->height -= 1;
				checkbal(key);
				p = true;
			}
			else {
				par = rt;
				rt = rt->left;
			}
		}
	}
}

bool tree::deleten(string x) {		
	node* n = NULL;
	node* parent = n;
	n = searchp(root, x, parent);
	if (n == NULL) return false;
	else
		if ((n->left == NULL) && (n->right == NULL)) {		//it is a leaf node
			if (parent->left == n) {
				parent->height += 1;
				delete n;
				parent->left = NULL;
				checkbal(parent->key);
				return true;
			}
			else {
				parent->height -= 1;
				delete n;
				parent->right = NULL;
				checkbal(parent->key);
				return true;
			}
		}
		else
			if ((n->left == NULL) || (n->right == NULL)) {				//if one of the subtrees is empty
				if (n->left == NULL) {
					if (parent->left == n) {
						parent->height += 1;
						parent->left = n->right;
						delete n;
						checkbal(parent->key);
						return true;
					}
					else {
						parent->height -= 1;
						parent->right = n->right;
						delete n;
						checkbal(parent->key);
						return true;
					}
				}
				else {				//which means that the right subtree is the one that is empty
					if (parent->left == n) {
						parent->height += 1;
						parent->left = n->left;
						delete n;
						checkbal(parent->key);
						return true;
					}
					else {
						parent->height -= 1;
						parent->right = n->left;
						delete n;
						checkbal(parent->key);
						return true;
					}
				}
			}
			else {			//if neither the left or right tree are empty
				int* check = new int;
				*check = 1;
				node* succ = findsucc(n);
				n->key = succ->key;
				succ->key = "-1";
				n->height += 1;
				n->left->height += 1;
				deleten(succ->key);
				checkbal(n->key);
				return true;
			}
}

node* tree::findsucc(node* key) {
	node* cursor = key->left;
	while (cursor->right != NULL) cursor = cursor->right;
	return cursor;
}

void tree::checkbal(string key) {			
	node* tracker = root;
	while (true) {
		if (key == tracker->key) break;		//go through all parents until you reach desired node
		if ((tracker->height > 1) || (tracker->height < -1)) {		//unbalanced
			node* cur;
			if (tracker->height > 1) {		//deeper right
				if (tracker->right->right != NULL) {
					//left turn
					cur = tracker->right;
					tracker->right = NULL;
					cur->left = tracker;
					tracker->height -= 2;
					cur->height -= 1;
				}
				else {
					//right left rotation
					node* cur2;
					cur = tracker->right;
					cur2 = tracker->right->left;
					tracker->right = NULL;
					cur->left = NULL;
					cur2->right = cur;
					cur2->left = tracker;
					tracker->height -= 2;
					cur->height -= 1;
				}
			}
			else {		//deeper left
				if (tracker->left->left != NULL) {
					//right rotation
					cur = tracker->left;
					tracker->left = NULL;
					cur->right = tracker;
					tracker->height += 2;
					cur->height += 1;
				}
				else {
					//left right rotation
					node* cur2 = tracker;
					cur = tracker->left;
					cur2 = tracker->left->right;
					tracker->left = NULL;
					cur->right = NULL;
					cur2->left = cur;
					cur2->right = tracker;
					tracker->height += 2;
					cur->height += 1;
				}
			}
		}
		else {		//finding key
			if (key > tracker->key) tracker = tracker->right;
			else tracker = tracker->left;
		}
		checkbal(tracker->key);
	}
}

void tree::display() {
	cout << "Root: " << root->key << "\n";
	if (root->left != NULL) {
		cout << "Left \n";
		tleft(root->left);
	}
	if (root->right != NULL) {
		tright(root->right);
	}
}

void tree::tleft(node* left) {
	cout << "Left: " << left->key;
	if (left->left != NULL) {
		cout << "\n";
		tleft(left->left);
	}
	if (left->right != NULL) {
		tright(left->right);
	}
}

void tree::tright(node* right) {
	cout << "Right " << right->key;
	if (right->left != NULL) {
		cout << "\n";
		tleft(right->left);
	}
}