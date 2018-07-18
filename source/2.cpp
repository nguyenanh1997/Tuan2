#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 1000
FILE *Kiem_tra_file(char *ten_file)
{
    int bien_dem,kich_co;
    printf("%s\n",ten_file);
    FILE *con_tro_file = fopen(ten_file,"r");
    // kiểm tra có mở được file hay không
    if(con_tro_file != NULL)
    {
        char du_lieu_lay_tu_file[1000];
        int co = 1;
        while(feof(con_tro_file) != NULL)
        {
            // lấy từng dòng trong file
                fgets(du_lieu_lay_tu_file,1000,con_tro_file);
                for(bien_dem = 0;bien_dem<strlen(du_lieu_lay_tu_file);bien_dem++)
                {
                    kich_co = du_lieu_lay_tu_file[bien_dem];
                    // kiểm tra xem file có dữ liệu nào nằm ngoài phạm vi ký tự cho phép hay không
                    if(kich_co < 33 || kich_co == 127)
                    {
                        co = 2;
                        break;
                    }
                }
        }
        if(co == 2) // nếu có ký tự không hợp lê thì không làm tiếp nữa
            printf("trong file chua ky tu khong hop le\n");
        else return con_tro_file; // nếu không thì trả về con trỏ file
    }
    else printf("khong the tim thay file\n"); // không tìm thấy file cần tìm
}
void nhap_ten_file(char *ten_file)
{
    // nhập tên file
    printf("de nghi nhap ten file\n");
    fflush(stdin);
    gets(ten_file);
}
void thay_the(char *chuoi_can_thay_the, const char *tu_cu, const char *tu_moi)
{
    char *vi_tri_tim_thay_tu, chuoi_tam[1000];
    int vi_tri , do_dai_tu_cu;
    vi_tri = 0;
    // lấy độ dài từ cũ
    do_dai_tu_cu = strlen(tu_cu);
    // tìm kiếm vị trí từ cũ trong chuỗi cần thay thế
    while ((vi_tri_tim_thay_tu = strstr(chuoi_can_thay_the, tu_cu)) != NULL)
    {
        // copy chuỗi cần thay thế lại
        strcpy(chuoi_tam, chuoi_can_thay_the);
        // lấy vị trí của từ đó trong chuỗi cần thay thế
        vi_tri = vi_tri_tim_thay_tu - chuoi_can_thay_the;
        // xóa bỏ các phần tử phía sau vị trí vừa tìm được
        chuoi_can_thay_the[vi_tri] = '\0';
        // copy từ mới vào cuối chuỗi cần thay thế
        strcat(chuoi_can_thay_the, tu_moi);
        // copy những phần tử phía sau phần tử từ cũ trong chuỗi tạm vào chuỗi cần thay thế
        strcat(chuoi_can_thay_the, chuoi_tam + vi_tri + do_dai_tu_cu);
    }
}

int so_lan_xuat_hien(char *ten_file,char tu_khoa[],char tu_thay_the[],int chuc_nang)
{
    char du_lieu_1_dong_trong_file[1000], tenFileTam[100] = "file.tmp", tenFOut[100] = "OUTPUT.txt";
    int bien_dem, gia_tri_cua_1_chu_trong_dong, gia_tri_cua_1_chu_trong_tu_khoa, vi_tri_sau_bien_dem, dem_dong, bien_dem_cua_tu_khoa, co,dem_lan_xuat_hien;
    bien_dem = 0;
    vi_tri_sau_bien_dem = 0;
    dem_dong = 0;
    dem_lan_xuat_hien = 0;
    FILE *con_tro_file_can_thao_tac, *file_tam, *file_dau_ra;
    // kiểm tra file cần thao tác
    con_tro_file_can_thao_tac = Kiem_tra_file(ten_file);
    // mở file ghi lịch sử
    file_dau_ra = fopen(tenFOut,"a+");
    // tạo 1 file tạm để chứa dữ liệu sau khi sửa
    file_tam = fopen(tenFileTam,"a+");
    // ghi vào file đầu ra lịch sử
    fputs(ten_file,file_dau_ra);
    fputs(" \n ",file_dau_ra);
    // kiểm tra xem người dùng nhập chức năng nào rồi ghi nội dung vào file đầu ra
    if(chuc_nang == 1)
    {
        fputs("chuc nang 1\n",file_dau_ra);
        fputs("tu khoa la: ",file_dau_ra);
        fputs(tu_khoa,file_dau_ra);
        fputs(" \n ",file_dau_ra);
    }
    else {
        fputs("chuc nang 2\n tu thay the la: ",file_dau_ra);
        fputs(tu_thay_the,file_dau_ra);
        fputs("tu khoa la: ",file_dau_ra);
        fputs(tu_khoa,file_dau_ra);
        fputs(" \n ",file_dau_ra);
    }
    printf("tu khoa la : %s\n",tu_khoa);
    // duyệt file cần thao tác
    while( feof(con_tro_file_can_thao_tac) == 0 )
    {
        // lấy từng dòng trong file cần thao tác để đếm xem có bao nhiêu dòng nhưng nếu trong file txt mà dòng dài hơn 1000 từ thì đếm dòng sẽ sai dùng cấp phát động thì tốt hơn
            fgets( du_lieu_1_dong_trong_file, 1000, con_tro_file_can_thao_tac);
            dem_dong++;
            // duyệt từng phần tử trong dòng vừa lấy
            for(bien_dem = 0; bien_dem < strlen(du_lieu_1_dong_trong_file);bien_dem++)
            {
                // lấy giá trị của chữ đầu tiên trong từ khóa
                gia_tri_cua_1_chu_trong_tu_khoa = tu_khoa[0];
                // lấy giá trị của chữ trong dòng vừa nhận được
                gia_tri_cua_1_chu_trong_dong = du_lieu_1_dong_trong_file[bien_dem];
                // so sánh giá trị của chúng xem có bằng nhau hay không
                if(gia_tri_cua_1_chu_trong_dong == gia_tri_cua_1_chu_trong_tu_khoa  || (gia_tri_cua_1_chu_trong_dong - 32)== gia_tri_cua_1_chu_trong_tu_khoa || (gia_tri_cua_1_chu_trong_dong + 32) == gia_tri_cua_1_chu_trong_tu_khoa|| (gia_tri_cua_1_chu_trong_tu_khoa - 32) == gia_tri_cua_1_chu_trong_dong || (gia_tri_cua_1_chu_trong_tu_khoa + 32) == gia_tri_cua_1_chu_trong_dong)
                {
                    // lấy vị trí của chữ phía sau biến đếm
                    vi_tri_sau_bien_dem = bien_dem + 1;
                    // vị trí của chữ thứ 2 trong từ khóa
                    bien_dem_cua_tu_khoa = 1;
                    // duyệt theo số lượng phần tử còn lại trong từ khóa
                    while(bien_dem_cua_tu_khoa < strlen(tu_khoa))
                    {
                        // lại lấy giá trị của từng chữ
                        gia_tri_cua_1_chu_trong_dong= du_lieu_1_dong_trong_file[vi_tri_sau_bien_dem];
                        gia_tri_cua_1_chu_trong_tu_khoa = tu_khoa[bien_dem_cua_tu_khoa];
                        // so sánh giá trị của 2 chữ
                        if(gia_tri_cua_1_chu_trong_dong == gia_tri_cua_1_chu_trong_tu_khoa  || (gia_tri_cua_1_chu_trong_dong - 32)== gia_tri_cua_1_chu_trong_tu_khoa || (gia_tri_cua_1_chu_trong_dong + 32) == gia_tri_cua_1_chu_trong_tu_khoa|| (gia_tri_cua_1_chu_trong_tu_khoa - 32) == gia_tri_cua_1_chu_trong_dong || (gia_tri_cua_1_chu_trong_tu_khoa + 32) == gia_tri_cua_1_chu_trong_dong)
                        {
                            bien_dem_cua_tu_khoa++;
                            vi_tri_sau_bien_dem++;
                            co = 1;
                        }
                        else // nếu có 1 từ khác thì thoát ra ngoài vòng lặp để tìm kiếm từ tiếp theo
                        {
                            co = 0;
                            break;
                        }
                    }
                    // kiểm tra xem có tìm thấy không
                    if(co == 1)
                    {
                        dem_lan_xuat_hien++;
                        printf("dong %d cach dau dong %d \n", dem_dong,bien_dem);
                        // ghi ra file lịch sử
                        fputs("dong ",file_dau_ra);
                        fprintf(file_dau_ra,"%d",dem_dong);
                        fputs(" cach dau dong ",file_dau_ra);
                        fprintf(file_dau_ra,"%d",bien_dem);
                        fputs(" \n ",file_dau_ra);
                    }
                }
            }
            // kiểm tra chúc năng
            if(chuc_nang == 2)
            {
                // thay thế từ khóa trong dòng vừa lấy
                thay_the(du_lieu_1_dong_trong_file,tu_khoa,tu_thay_the);
                // ghi dòng đã được sửa đổi vào file tạm
                fputs(du_lieu_1_dong_trong_file,file_tam);
            }
    }
    fclose(con_tro_file_can_thao_tac);
    fclose(file_tam);
    if(chuc_nang == 2)  // thay thế file đang thao tác bằng file tạm
    {
        remove(ten_file);
        rename(tenFileTam,ten_file);
    }
    printf("so lan xuat hien la: %d \n",dem_lan_xuat_hien);
    fputs("so lan xuat hien la: ",file_dau_ra);
    fprintf(file_dau_ra,"%d",dem_lan_xuat_hien);
    fputs("\n",file_dau_ra);
    return 0;
}
void tim_kiem(char *ten_file,int chuc_nang)
{
    char tu_khoa[20], tu_thay_the[20];
    printf("de nghi nhap tu khoa\n");
    fflush(stdin);
    // lấy từ khóa
    gets(tu_khoa);
    // kiểm tra chức năng
    if(chuc_nang == 2)
    {
        printf("tu de thay the la: \n");
        fflush(stdin);
        // lấy từ thay thế
        gets(tu_thay_the);
    }
    // thực hiện chức năng tìm kiếm và thay thế
    so_lan_xuat_hien(ten_file,tu_khoa,tu_thay_the,chuc_nang);
}
int main()
{
    char ten_file[100];
    int chuc_nang;
    printf("nhap file ban muon tim\n");
    fflush(stdin);
    gets(ten_file);
    do
    {
        printf("chuc nang:\n");
        printf("1: tim tu\n");
        printf("2: tim va sua tu\n");
        printf("3 ket thuc\n");
        printf("nhap chuc nang\n");
        scanf("%d",&chuc_nang);
        switch(chuc_nang)
        {
            case 1:
            case 2:
            tim_kiem(ten_file,chuc_nang) ; break;
            case 3: break;
        }
    }while(chuc_nang != 3);
    return 0;
}
