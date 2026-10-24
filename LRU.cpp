#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int key, value;
    Node* prev;
    Node* next;

    Node(int k, int v) { // initialize key and values to Node.
        key = k;
        value = v;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertAtTail(Node* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

public:
    LRUCache(int cap) {
        capacity = cap;

        head = new Node(0, 0);
        tail = new Node(0, 0);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;

        Node* node = cache[key];

        removeNode(node);
        insertAtTail(node);

        return node->value;
    }

    void put(int key, int value) {
        if (capacity <= 0)
            return;

        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            removeNode(node);
            insertAtTail(node);
            return;
        }

        if (cache.size() == capacity) {
            Node* lru = head->next;
            removeNode(lru);
            cache.erase(lru->key);
            delete lru;
        }

        Node* node = new Node(key, value);
        insertAtTail(node);
        cache[key] = node;
    }

    LRUCache() {
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    LRUCache lru(2);

    lru.put(1, 10);
    lru.put(2, 20);

    cout << lru.get(1) << endl;

    lru.put(3, 30);

    cout << lru.get(2) << endl;
    cout << lru.get(3) << endl;

    return 0;
}
