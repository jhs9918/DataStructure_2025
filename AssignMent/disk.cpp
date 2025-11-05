#include <iostream>
#include <list>
#include <sstream>
using namespace std;

struct Seg {
    string name;
    int start, size, free;
};

list<Seg> disk;
int cap;

void upd() {
    int p = 0;
    for (auto& s : disk)
        s.start = p, p += s.size;
}

void merge() {
    for (auto i = disk.begin(); i != disk.end(); i++)
        if (i->free) {
            auto j = i;
            j++;
            while (j != disk.end() && j->free) {
                i->size += j->size;
                j = disk.erase(j);
            }
        }
    upd();
}

int ex(string name) {
    for (auto& s : disk)
        if (!s.free && s.name == name)
            return 1;
    return 0;
}

void write(string name, int size) {
    if (ex(name))
        return void(cout << "error\n");
    int t = 0;
    for (auto& s : disk)
        t += s.free ? s.size : 0;
    if (t < size)
        return void(cout << "diskfull\n");

    for (auto i = disk.begin(); i != disk.end(); i++)
        if (i->free && i->size >= size) {
            int r = i->size - size;
            i->name = name, i->size = size, i->free = 0;
            if (r)
                disk.insert(++i, {"", 0, r, 1});
            return upd();
        }

    for (auto i = disk.begin(); i != disk.end() && size; i++)
        if (i->free) {
            int w = min(size, i->size), r = i->size - w;
            i->name = name, i->size = w, i->free = 0, size -= w;
            if (r)
                i = disk.insert(++i, {"", 0, r, 1});
        }
    upd();
}

void del(string name) {
    if (!ex(name))
        return void(cout << "error\n");
    for (auto& s : disk)
        if (s.name == name)
            s.name = "", s.free = 1;
    merge();
}

void show(string name) {
    if (!ex(name))
        return void(cout << "error\n");
    int f = 1;
    for (auto& s : disk)
        if (s.name == name)
            (!f ? cout << " " : cout), cout << s.start, f = 0;
    cout << "\n";
}

void compact() {
    list<Seg> nd;
    int p = 0;
    for (auto& s : disk)
        if (!s.free)
            nd.push_back({s.name, p, s.size, 0}), p += s.size;
    if (p < cap)
        nd.push_back({"", p, cap - p, 1});
    disk = nd;

    for (auto i = disk.begin(); i != disk.end(); i++)
        if (!i->free) {
            auto j = i;
            j++;
            while (j != disk.end() && !j->free && j->name == i->name)
                i->size += j->size, j = disk.erase(j);
        }
    upd();
}

int main() {
    cin >> cap;
    cin.ignore();
    disk.push_back({"", 0, cap, 1});

    string l, cmd, name;
    int size;
    while (getline(cin, l)) {
        istringstream s(l);
        s >> cmd;

        if (cmd == "end")
            break;
        if (cmd == "write")
            s >> name >> size, write(name, size);
        else if (cmd == "delete")
            s >> name, del(name);
        else if (cmd == "show")
            s >> name, show(name);
        else
            compact();
    }
}
