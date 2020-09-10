#ifndef DIGEST_H
#define DIGEST_H
class Digest {
    public:
    void set_data(void* d) { data = d; }
    void* get_data() { return data; }

    private:
    void *data;
};
#endif
