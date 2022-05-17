# 2048_SDL2

***

# 1. Giới thiệu

-Ý tưởng: Từ game 2048 cổ điển

-Ngôn ngữ: C++

-Đồ họa em dùng là SDL2. Em học ở https://lazyfoo.net/tutorials/SDL/index.php

-Hình ảnh em lấy trên mạng và cắt ghép

-Âm thanh em lấy ở:
https://www.chosic.com/download-audio/29771/

https://www.chosic.com/download-audio/29514/
                   
-Cách cài đặt chương trình: Em code dự án này bằng visual studio 2019, do đó có 2 cách chạy chương trình: (Đảm bảo đã tải Visual studio 2019 hoặc hơn)

  - Cách 1: Mở file x64/Debug/2048_Version_0.4.exe
  - Cách 2: Mở file 2048_Version_0.4.sln và chạy chương trình trên Visual Studio 


# 2. Cách chơi & luật chơi

2.1 Cách chơi.

-Người chơi nhấn các phím W,A,S,D để di chuyển các ô số trên ma trận 4x4 để ghép 2 ô có giá trị giống nhau thành ô có giá trị gấp đôi

2.2 Luật chơi.

-Điều kiện thắng: Có 1 ô đạt 2048

-Điều kiện thua: Bàn cờ 4x4 bị lấp đầy và không thể di chuyển được nữa

# 3. Thuật toán của game

-Đầu tiên, spawn ra 1 giá trị bất kì, sau đó người chơi đi 1 nước

-Sau khi người chơi đi 1 nước, spawn ra thêm 1 giá trị tiếp 

-Để check xem người chơi còn có thể di chuyển được nữa hay không, trước tiên em check xem ma trận đã đầy hay chưa, nếu đầy rồi thì duyệt cả ma trận với từng cặp 2 ô liền kề nhau (ngang, dọc). Nếu duyệt cả bàn cờ mà không có 2 ô nào có giá trị bằng nhau thì người chơi thua.

# 4. Các chức năng đã cài đặt:

-Hình ảnh, nhạc, sound effect

-Save game

-Pause game: ấn ESC trong lúc đang chơi để chuyển màn hình về trạng thái pause, trong màn hình pause ấn ESC lần nữa để trở về màn hình chính.

-Game loop: Sau khi người chơi thắng/ thua, có thể chơi lại bằng cách ấn vào "Play Again"

-Link video test: https://youtu.be/xqqdrCn1hMA

# 5. Các kĩ thuật lập trình

-Mảng, con trỏ, vector, string, enum, class 

-SDL2: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

# 6. Nhận xét

-Đồ họa, âm thanh game khá ổn 

-Dự án này em hoàn toàn tự làm và không có sao chép ở bất kì đâu

-Hướng phát triển: Làm bảng xếp hạng, chơi nhiều người,...
