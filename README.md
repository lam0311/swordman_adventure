Tên: Lưu Tùng Lâm. 
MSV: 24021545.

Chủ đề game : Game của em thuộc thể loại hành động 2D (2D action game) với phong cách fantasy dark pixel art,nơi người chơi chiến đấu với goblin và boss bằng kiếm và kỹ năng đặc biệt.


Ngưỡng điểm em cho là xứng đáng : 9-10đ


Các lí do bảo vệ ngưỡng điểm đó:

+ Các thuật toán hầu hết đều nằm ngoài trương trình học (trừ một số sự kiện chuột, bàn phím, tải ảnh,...) đủ rắc rối để đạt điểm cao.

+ Game có đồ họa không đơn giản, mọi thứ đều cop nhặt trên mạng các hình ảnh, em dùng khá nhiều hình ảnh nên đồ họa được coi ở mức trung bình.

+ Game có âm thanh đầy đủ ở hầu hết các hành động phát ra âm thanh như : nhạc menu, nhạc game, tiếng bước chân, chém, bị đánh, bom nổ...

+ Hình ảnh phong phú đẩy đủ, rất nhiều hoạt hình chuyển động trông khá bắt mắt.

+ Map được làm bằng tile map và tự viết 460*12 ô vuông đặt trong file txt.

+ Cơ chế xây dựng map theo màn hình camera hiển thị, camera chạy tới đâu map theo tới đấy xóa phần không xuất hiện trên màn hình cam, nhân vật di chuyển nhưng thực ra đang đứng yên và chỉ có map được xây dựng liên tục tạo cảm giác di chuyển, cơ chế camera rung tạo cảm giác kịch tính, cơ chế slow motion (fps).

+ Cơ chế trọng lực khiến cho nhân vật bị hút xuống phía dưới, cơ chế va chạm với map để nhân vật không đi xuyên qua đất và cũnng như bị các vật cản cản lại.

+ Cơ chế dùng chiêu đặc biệt có thanh nộ trên đầu giữ phím đầy thanh nổ thì sài được chiêu, có cột hp và cột tích năng lượng để dùng chiêu đặc biệt.  

+  các sự kiện phím mũi tên thay đổi vận tốc làm cho nhân vật di chuyển sang trái phải và nhảy lên, chuyển sang hoạt ảnh chém khi nhấn chuột trái, tạo ra class quái vật cơ chế đuổi theo nhân vật khi tới gần, tạo ra class đạn, ném bom từ xa
chém khi khoảng cách đủ, rất nhiều cơ chế va chạm, tạo ra boss với 3 cơ chế bắn đạn khác nhau tùy từng giai đoạn.

+ nhân vật có 3 chiêu khác nhau và chiêu lướt , quái có 2 chiêu và boss có 3 chiêu.

+ có 5 màn hình : menu, help, start, victory, defeated.

+ Tính điểm và khi thắng hoặc thất bại điểm sẽ được công bố.

+ Các thuật toán đều là tự học xem trên slide, xem từ các nguồn trên kênh yutube, em có làm 1 game giống khủng long mất mạng trước đó, cách học của em là chỗ nào không biết thì hỏi AI và chấp vá làm game khủng long rồi đủ kĩ năng em mới bắt tay vào làm game chính.
 Link :
+ tìm ảnh, hoạt ảnh nhân vật, quái: https://itch.io/game-assets/free
+ âm thanh: https://pixabay.com/sound-effects/
+ mức độ dựa vào AI: Ban đầu xây dựng game khủng long mất mạng dựa vào AI, các nguồn trên yutube khá nhiều, không thể tự viết được, không biết code như nào. Sang game chính thì tất cả 10 ngón tay em tự code.
+ 1 só thuật toán va chạm map của nhân vật, class bullet thì xem trên yutube (https://www.youtube.com/watch?v=Heafds0qYRc&t=1707s), học trên video của cô (https://www.youtube.com/@tranthiminhchau9465), 1 số yutube nước ngoài (https://www.youtube.com/watch?v=iEn0ozP-jxc), (https://www.youtube.com/watch?v=NPdAQlsrOIY), các tutorial (https://www.youtube.com/watch?v=gOXg1ImX5j0&list=PLYmIsLVSssdIOn5J71CVBblPlXici1_2A).
Check list:
+  Tự làm mọi thứ, không copy từ phần nào, chỗ nào sai, hay chưa đúng thì hỏi AI chỉ lỗi và chỉnh sửa lại.
+  em có ghi link tham khảo trên rồi.
+  Dùng SDL_RenderCopy,SDL_RenderFillRect để vẽ các khối vuông để xử lí va chạm rồi xóa, dùng SDL_SetTextureAlphaMod để làm mờ các ảnh khi render ra.
+  Dùng hơn 100 ảnh để xây dựng.
+  background: không dùng background cuộn chuyển động do không phù hợp, có 5 back ground cho 5 trạng thái game.
+  event bàn phím : space dùng chiêu đặc biệt, A sang trái ,D sang phải,W nhảy,E lướt.
+  event chuột :  chuột trái tấn công, chuột phải dùng chiêu tấn công xa
+  Animation (hoạt hình): nhân vật có hơn 12 hoạt hình khác nhau tính cả left right, quái thường có hơn 10 hoạt hình khác nhau, boss có hơn 6 hoạt hình , bullet thì 3 loại đạn với 6 hoạt hình đạn, hiệu ứng nhân vật có nhiều hoạt hình.
+  xử lí va chạm : xử lí va chạm map với nhân vật và quái, va chạm nhân vật và quái khi cận chiến và các va chạm bullet, có rất nhiều xử lí va chạm.
+  score: có tính số kill và tính điểm rồi công bố khi kết thúc.
+  Sound: có dùng nhiều âm thanh.
+  sound on off : có thể bật tắt âm thanh khi trong game.
+  background music: có ở tất cả 5 trạng thái game.
+  Font: dùng để làm tính kill và score.
+  Menu: có menu.
+  Status bar / lives: có thêm cả thanh năng lượng và thanh nộ.
+  Những điểm nổi bật em nói bên trên rồi, khả năng vẫn còn quên 1 số thứ, em trình bày lúc chấm bài sau.
+  Em chưa học oop, cấp 3 chưa từng viết code nên code em có thể không xịn, gọn gàng dễ nâng cấp nhưng mỗi hàm thì không quá dài.
