#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct tuyen_duong
{
    int x;
    int y;
    int dem;
    struct tuyen_duong *tiep;
}Tuyen_Duong;
Tuyen_Duong *danh_sach_1 = NULL;
Tuyen_Duong *danh_sach_2 = NULL;
void tao_nut(int x,int y,int so_thu_tu,int danh_sach)
{
    Tuyen_Duong *con_tro;
    con_tro = (Tuyen_Duong *)malloc(sizeof(Tuyen_Duong));
    con_tro->x = x;
    con_tro->y = y;
    con_tro->dem = so_thu_tu;
    if(danh_sach == 2)
    {
        con_tro->tiep = danh_sach_2;
        danh_sach_2 = con_tro;
    }
    else
    {
        con_tro->tiep = danh_sach_1;
        danh_sach_1 = con_tro;
    }
}
void xoa(int so_thu_tu)
{
    Tuyen_Duong *con_tro_hien_tai = danh_sach_1;
    Tuyen_Duong *con_tro_truoc_con_tro_hien_tai = NULL;
    while( con_tro_hien_tai->dem != so_thu_tu)
     {
         con_tro_truoc_con_tro_hien_tai = con_tro_hien_tai;
         con_tro_hien_tai = con_tro_hien_tai->tiep;
     }
    if(con_tro_hien_tai == danh_sach_1)
    danh_sach_1 = con_tro_hien_tai->tiep;
    else
    con_tro_truoc_con_tro_hien_tai->tiep = con_tro_hien_tai->tiep;
    free(con_tro_hien_tai);
}
void in(Tuyen_Duong *danh_sach)
{
    FILE *con_tro_file;
    Tuyen_Duong *con_tro;
    con_tro = danh_sach;
    con_tro_file = fopen("OUTPUT.txt","a+");
    printf("in file OUTPUT.txt \n");
    fprintf(con_tro_file,"%d ",con_tro->y);
    while(con_tro != NULL)
    {
        fprintf(con_tro_file,"%d ",con_tro->x);
        con_tro = con_tro->tiep;
    }
    fclose(con_tro_file);
    printf("Da in ra xong\n mo file OUTPUT.txt de xem ket qua");
}
void tim_duong(int n,int u,int v)
{
    Tuyen_Duong *con_tro_danh_sach_1, *con_tro_danh_sach_2, *con_tro_3;
    // biến y dùng để lưu lại tọa độ y của con trỏ trước
    // biến co dùng để kiểm tra xem đã tìm thấy đường tiếp theo phù hợp chưa
    int dem, co, y;
    dem=0;
    con_tro_danh_sach_2 = (Tuyen_Duong *)malloc(sizeof(Tuyen_Duong));
    con_tro_danh_sach_1 = danh_sach_1;
    while(con_tro_danh_sach_1 != NULL) // Duyệt danh_sach_1
    {
        if1: if( con_tro_danh_sach_1->x == u) // so sánh xem giá trị x của con_tro_danh_sach_1 có bằng tọa độ xuất phát không
		{
                dem = 1;
				y = con_tro_danh_sach_1->y; // lưu tọa độ y lại
				tao_nut(con_tro_danh_sach_1->x,con_tro_danh_sach_1->y,dem,2); // thêm con trở vừa tìm thấy vào danh sách 2
				xoa(con_tro_danh_sach_1->dem); //  xóa con trỏ đó ra khỏi danh sách 1;
				con_tro_danh_sach_1 = danh_sach_1; // cho con_tro_danh_sach_1 về đầu danh_sach_1
            // thực hiện duyệt tiếp danh_sach_1
			do{
				if(con_tro_danh_sach_1->x == y) // nếu bắt gặp con trỏ nào có x == với y của con trỏ trước thì thực hiện
				{
				    dem++;
					y = con_tro_danh_sach_1->y; // lưu lại tọa độ y
					tao_nut(con_tro_danh_sach_1->x,con_tro_danh_sach_1->y,dem,2);  // thêm con trở vừa tìm thấy vào danh sách 2
					xoa(con_tro_danh_sach_1->dem); //  xóa con trỏ đó ra khỏi danh sách 1;
					if(y == v) // nếu tọa độ y đó đã là điểm đến thì dừng
					{
					    co = 1; // để ra ngoài có thể dừng lại
					    break;
                    }
					con_tro_danh_sach_1 = danh_sach_1; // đưa con trỏ về đầu danh sách nếu không chưa đến điểm kết thúc
					if( dem >n) break; // nếu vượt quá số tuyến phố quy định hoặc bị quay lại phía đầu thì thoat ra ngoài
                    con_tro_3 = danh_sach_2;
                    // duyệt danh sách 2
					while(con_tro_3 != NULL)
                    {
                        if(con_tro_danh_sach_1->y == con_tro_3->x) // tìm kiếm xem tọa độ vừa tìm thấy có làm quay lại 1 tuyến phố nào không
                        {
                            if(con_tro_3->tiep == NULL) // nếu là con nút cuối cùng trong danh sách thì xóa nút đó luôn
                                break;
                            else
                                danh_sach_2 = danh_sach_2->tiep; // xóa nút đầu danh sách
                        }
                        con_tro_3 = con_tro_3->tiep;
                    }
				}
				else
				{
				    // nếu không tìm thấy con nút phù hợp thì duyệt tiếp trong danh_sach_1
						con_tro_danh_sach_1 = con_tro_danh_sach_1->tiep;
						// đánh dấu chưa tìm thấy
						co = 0;
						// kiểm tra đã hết danh_sach_1 chưa
						if(con_tro_danh_sach_1 == NULL)
                        {
                                con_tro_danh_sach_1 = danh_sach_1; // đưa con trỏ về đầu
                                // kiểm tra có phải đầu danh sách không để xóa
                                if(danh_sach_2->dem == 1)
                                {
                                    danh_sach_2 = NULL;
                                }
                                else
                                {
                                    danh_sach_2 = danh_sach_2->tiep;
                                }
						}
						if(danh_sach_2 == NULL) {goto if1;}
				}
			}while(con_tro_danh_sach_1 != NULL);
            if(co == 1) break; // kiểm tra xem đã tìm thấy chưa
		}
        if(co == 1)
        {
            break;
        }
        // nếu chưa duyệt hết danh sách thì duyệt tiếp để tìm nút chứa vị trí xuất phát
        if(con_tro_danh_sach_1 != NULL)
        {
            con_tro_danh_sach_1 = con_tro_danh_sach_1->tiep;
        }

    }
}
int main()
{
    int n ,m ,u ,v ,x ,y ,so_thu_tu;; // các tham số của đầu bài, tọa độ của tuyến đường và số thứ tự để thêm vào nút
    FILE *con_tro_file;
    so_thu_tu = 0;
    char ten_file[100];
    printf("nhap vi tri luu file INPUT\n");
    fflush(stdin);
    gets(ten_file);
    con_tro_file = fopen(ten_file,"a+");
    fscanf(con_tro_file,"%d",&n);
    fscanf(con_tro_file,"%d",&m);
    fscanf(con_tro_file,"%d",&u);
    fscanf(con_tro_file,"%d",&v);
    while(!feof(con_tro_file))
    {
        so_thu_tu++;
        fscanf(con_tro_file,"%d",&x);
        fscanf(con_tro_file,"%d",&y);
        tao_nut(x,y,so_thu_tu,1); // đưa dữ liệu vào danh_sach_1
    }
    fclose(con_tro_file);
    tim_duong(n,u,v); // đưa số tuyến phố, vị trí bắt đầu và vị trí kết thúc vào để so sánh
    in(danh_sach_2); // ghi kết quả ra file OUTPUT.txt
    return 0;
}
