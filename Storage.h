#ifndef STORAGE_H
#define STORAGE_H

// Generic template class to store any type
// Uses a static array of size 100 (no vectors allowed)
template <typename T>
class Storage {
private:
    T data[100];
    int count;

public:
    Storage() {
        count = 0;
    }

    // Add an item to storage
    bool add(const T& item) {
        if (count >= 100) {
            return false; // storage full
        }
        data[count] = item;
        count++;
        return true;
    }

    // Remove item by ID (finds by getId())
    bool removeById(int id) {
        int index = -1;
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                index = i;
                break;
            }
        }
        if (index == -1) return false;

        // Shift elements left
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
        return true;
    }

    // Find item by ID, returns pointer or nullptr if not found
    T* findById(int id) {
        for (int i = 0; i < count; i++) {
            if (data[i].getId() == id) {
                return &data[i];
            }
        }
        return nullptr;
    }

    // Get all items (returns pointer to array)
    T* getAll() {
        return data;
    }

    // Get current count
    int size() const {
        return count;
    }

    // Clear all
    void clear() {
        count = 0;
    }
};

#endif
