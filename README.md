# 2048_SDL2

***

# 1. Giới thiệu

-Đồ họa em dùng là SDL2. Em học ở https://lazyfoo.net/tutorials/SDL/index.php

-Hình ảnh em lấy trên mạng và cắt ghép

-Âm thanh em lấy ở:
https://www.chosic.com/download-audio/29771/

https://www.chosic.com/download-audio/29514/
                   

# 2. Cách chơi & luật chơi

2.1 Cách chơi.

-Người chơi nhấn các phím W,A,S,D để di chuyển các ô số trên ma trận 4x4 để ghép 2 ô có giá trị giống nhau thành ô có giá trị gấp đôi

2.2 Luật chơi.

-Điều kiện thắng: Có 1 ô đạt 2048

-Điều kiện thua: Bàn cờ 4x4 bị lấp đầy và không thể di chuyển được nữa

# 3. Thuật toán của game

-Đầu tiên, spawn ra 1 giá trị bất kì, sau đó người chơi đi 1 nước

-Sau khi người chơi đi 1 nước, spawn ra thêm 1 giá trị tiếp 

-Để check xem người chơi còn có thể di chuyển được nữa hay không, trước tiên em check xem ma trận đã đầy hay chưa, nếu đầy rồi thì duyệt cả ma trận với 2 ô liền kề nhau (ngang, dọc). Nếu duyệt cả bàn cờ mà không có 2 ô nào có giá trị bằng nhau thì người chơi thua.

# 4. Nhận xét

-Đồ họa, âm thanh game tạm chấp nhận được 

-Em xin tự đánh giá dự án của mình được 8,5 điểm.
