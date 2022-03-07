struct Trade {
    int stk_code;
    int bid_id;
    int ask_id;
    double price;
    int volume;
}__attribute__((packed));

struct Order {
    int order_id;
    int price;
    int volume;
    unsigned char combined;
}__attribute__((packed));
