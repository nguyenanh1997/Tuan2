#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct ngoac
{
    char du_lieu;
    int so_thu_tu;
    struct ngoac *tiep;
}Ngoac;
Ngoac *dau_danh_sach = NULL;
Ngoac *Tao_nut(char du_lieu,int so_thu_tu)
{
    // lấy dữ liệu vào nút
    Ngoac *dau_ngoac = (Ngoac *)malloc(sizeof(Ngoac));
    dau_ngoac->du_lieu = du_lieu;
    dau_ngoac->so_thu_tu = so_thu_tu;
    return dau_ngoac;
}
void Them(char du_lieu[])
{
    int dem;
    dem = 0;
    // lập 1 danh sách liên kết đơn từ chuỗi dấu ngoặc lấy được
    do{
        Ngoac *dau_ngoac = (Ngoac *)malloc(sizeof(Ngoac));
        dau_ngoac = Tao_nut(du_lieu[dem],dem);
        dem++;
        printf("%c ",dau_ngoac->du_lieu);
        // nối nút vừa được tạo vào đầu danh sách
        dau_ngoac->tiep = dau_danh_sach;
        dau_danh_sach = dau_ngoac;
    }while(du_lieu[dem] != '\0');
}
void Xoa(int so_thu_tu)
{
    Ngoac *dau_ngoac_de_duyet, *dau_ngoac_phia_truoc_dau_ngoac_duyet;
    dau_ngoac_de_duyet = dau_danh_sach;
    dau_ngoac_phia_truoc_dau_ngoac_duyet = NULL;
    // tìm vị trí cần xóa
    while(dau_ngoac_de_duyet->so_thu_tu != so_thu_tu)
     {
         dau_ngoac_phia_truoc_dau_ngoac_duyet = dau_ngoac_de_duyet;
         dau_ngoac_de_duyet = dau_ngoac_de_duyet->tiep;
     }
     // kiểm tra xem vị trí cần xóa có phải là đầu danh sách không
     if(dau_ngoac_phia_truoc_dau_ngoac_duyet == NULL)
     {
         dau_danh_sach = dau_danh_sach->tiep; // lùi con trỏ đầu danh sách về phía sau
     }
     else
     {
         dau_ngoac_phia_truoc_dau_ngoac_duyet->tiep = dau_ngoac_de_duyet->tiep; // xóa nút cần xóa
     }
     free(dau_ngoac_de_duyet);
}
void Kiem_tra()
{
    Ngoac *dau_ngoac_de_so_sanh, *dau_ngoac_phu_hop;
    dau_ngoac_de_so_sanh = dau_danh_sach;
    // duyệt danh sách cái dấu ngoặc
    while(dau_ngoac_de_so_sanh != NULL)
    {
        // xem xét dấu ngoặc thuộc loại gì
        if(dau_ngoac_de_so_sanh->du_lieu == ')')
        {
            // duyệt tiếp tìm kiếm đấu ngoặc phù hợp với nó
            for(dau_ngoac_phu_hop = dau_ngoac_de_so_sanh->tiep; dau_ngoac_phu_hop != NULL; dau_ngoac_phu_hop = dau_ngoac_phu_hop->tiep)
            {
                if(dau_ngoac_phu_hop->du_lieu == '(')
                {
                    // xóa 2 nút các chứa các dấu ngoặc vừa tìm được
                    Xoa(dau_ngoac_de_so_sanh->so_thu_tu);
                    Xoa(dau_ngoac_phu_hop->so_thu_tu);
                    break;
                }
            }
        }
        // xem xét dấu ngoặc thuộc loại gì
        if( dau_ngoac_de_so_sanh->du_lieu == ']')
        {
            // duyệt tiếp tìm kiếm đấu ngoặc phù hợp với nó
            for(dau_ngoac_phu_hop = dau_ngoac_de_so_sanh->tiep; dau_ngoac_phu_hop != NULL; dau_ngoac_phu_hop = dau_ngoac_phu_hop->tiep)
            {
                if(dau_ngoac_phu_hop->du_lieu == '[')
                {
                    // xóa 2 nút các chứa các dấu ngoặc vừa tìm được
                    Xoa(dau_ngoac_de_so_sanh->so_thu_tu);
                    Xoa(dau_ngoac_phu_hop->so_thu_tu);
                    break;
                }
            }
        }
        dau_ngoac_de_so_sanh = dau_ngoac_de_so_sanh->tiep;
    }
}
void In()
{
    FILE *con_tro_file;
    Ngoac *dau_ngoac_de_duyet_sanh_sach;
    int dem;
    dem = 0;
    dau_ngoac_de_duyet_sanh_sach = dau_danh_sach;
    con_tro_file = fopen("BRACKET.OUT","a+");
    // duyệt danh sách để đếm xem còn bao nhiêu dấu ngoặc
    while(dau_ngoac_de_duyet_sanh_sach != NULL)
    {
        dem++;
        dau_ngoac_de_duyet_sanh_sach = dau_ngoac_de_duyet_sanh_sach->tiep;
    }
    fprintf(con_tro_file,"%d",dem);
    fprintf(con_tro_file,"\n");
    dau_ngoac_de_duyet_sanh_sach = dau_danh_sach;
    // duyệt danh sách lấy dữ liệu
    while(dau_ngoac_de_duyet_sanh_sach != NULL)
    {
        // kiểm tra dấu ngoặc và đưa ra dấu ngoặc phù hợp với nó
        if( dau_ngoac_de_duyet_sanh_sach->du_lieu == '(')
        {
            fputc(')',con_tro_file);
            fprintf(con_tro_file,"%d",dau_ngoac_de_duyet_sanh_sach->so_thu_tu);
            fputc('\n',con_tro_file);
        }
        else
        {
            if(dau_ngoac_de_duyet_sanh_sach->du_lieu== ')')
               {
                   fputc('(',con_tro_file);
                    fprintf(con_tro_file,"%d",dau_ngoac_de_duyet_sanh_sach->so_thu_tu);
                    fputc('\n',con_tro_file);

               }
            else
            {
                if( dau_ngoac_de_duyet_sanh_sach->du_lieu == '[' )
                {
                    fputc(']',con_tro_file);
                    fprintf(con_tro_file,"%d",dau_ngoac_de_duyet_sanh_sach->so_thu_tu);
                    fputc('\n',con_tro_file);
                }
                else
                {
                    fputc('[',con_tro_file);
                    fprintf(con_tro_file,"%d",dau_ngoac_de_duyet_sanh_sach->so_thu_tu);
                    fputc('\n',con_tro_file);
                }
            }
        }

       dau_ngoac_de_duyet_sanh_sach = dau_ngoac_de_duyet_sanh_sach->tiep;
    }

}

int main()
{
    char du_lieu_dau_vao[100], ten_file[100];
    int bien_dem, kiem_tra_ky_tu;
    kiem_tra_ky_tu = 1;
    FILE *con_tro_file;
    printf("de nghi nhap ten file\( link file)\) \n");
    fflush(stdin);
    gets(ten_file);
    con_tro_file = fopen(ten_file,"r");
    if(con_tro_file != NULL)
    {
        printf("thanh cong roi\n");
        fscanf(con_tro_file,"%s",&du_lieu_dau_vao);
    }
    else
    {
        printf("khong tim thay file\n");
        return 0;
    }
    fclose(con_tro_file);
    printf("%s\n",du_lieu_dau_vao);
    // kiểm tra xem dữ liệu đầu vào có đúng những dấu ngoặc phù hợp không
    for(bien_dem = 0;bien_dem < strlen(du_lieu_dau_vao); bien_dem++)
    {
        if( du_lieu_dau_vao[bien_dem] != '(' && du_lieu_dau_vao[bien_dem] != ')' && du_lieu_dau_vao[bien_dem] != '[' && du_lieu_dau_vao[bien_dem] != ']')
        {
             kiem_tra_ky_tu = 0;
             break;
        }
    }
    if(kiem_tra_ky_tu == 0)
        printf("de nghi chay lai chuong trinh va nhap dung theo yeu cau\n");
    else{
        Them(du_lieu_dau_vao);
        Kiem_tra();
        In();
    }
}
