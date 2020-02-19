#include "Header.h"



int main() {
	string check;
	tree t;
	while (check != "-1") {
		cout << "Enter the string, to exit enter -1\n";
		cin >> check;
		if (check != "-1") {
			char com;
			cout << "To search for an element enter character s, to insert enter i, to delete enter x, to display enter d\n";
			cin >> com;
			switch (com) {
			case 's':
				if (t.search(check)) {
					cout << "element found\n";
				}
				else cout << "element not found\n";
				break;
			case 'i':
				if (t.insert(check)) cout << "successfully inserted\n";
				else "duplicate element\n";
				break;
			case 'x':
				if (t.deleten(check)) cout << "element deleted\n";
				else cout << "no such element\n";
				break;
			case 'd':
				t.display();
				break;
			default:
				cout << "incorrect input\n";
			}
		}
	}

	return 0;
}