#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define _CRT_SECURE_NO_DEPRECATE
//=================================================================================
//Phần Khai Báo 
//=================================================================================
//câu 1:
struct ThongTinHangHoa //Khai bao cau truc thong tin hang hoa
{
	char MaSoHangHoa[50];
	char TenNguoiGui[50];
	char DiaChiNguoiGui[50];
	char SoDienThoaiNguoiGui[50];
	char SoDienThoaiNguoiNhan[50];
	char DiaChiNguoiNhan[50];
	char TenNguoiNhan[50];
	float PhiChuyenHang;
	float TrongLuong;
	char LoaiHang[50];
};
//=================================================================================

typedef ThongTinHangHoa Itemtype; //Khai bao kieu du lieu Itemtype la kieu du lieu ThongTinHangHoa
struct SNode //Khai bao cau truc danh sach lien ket don
{
	Itemtype Info;
	SNode* Next;
};
struct Slist //Khai bao cau truc danh sach lien ket don
{
	SNode* Head;
	SNode* Tail;
};
//=================================================================================
//Các hàm hỗ trợ hàm MAIN
SNode* createSNode(Itemtype x);
void initSList(Slist &sl);
int isEmpty(Slist sl);
void showSNode(SNode* p);
void showSlist(Slist sl);
SNode* NhapThongTin();
void Menu(int DemTam);
int DemSNode(Slist sl, int &n);
void DoiKyTu(char a[50]);

//=================================================================================
//Câu 2:Tạo danh sách liên kết đơn chứa thông tin gói hàng bằng 2 cách: nhập từ bàn phím và đọc/ghi từ file txt
void createSlist(Slist &sl);
void ReadFile(Slist &sl);
void WriteFile(Slist sl);
//=================================================================================
//Câu 3:
//Chức năng thêm 
int insertHead(Slist &sl, SNode *p);
void insertMid(Slist &sl, int g);
int insertTail(Slist &sl, SNode* p);
//Chức năng xóa
int deleteHead(Slist &sl);
void deleteMid(Slist &sl, int n);
int deleteTail(Slist &sl);
//=================================================================================
//Câu 4:Sắp xếp hàng theo từng khu vực tỉnh thành của nơi nhận, trong từng nhóm tỉnh thành, thì sắp xếp theo thể loại 
void SapXep(Slist sl);
//=================================================================================
//Câu 5:
//Thêm 1 gói hàng x vào danh sách sao cho vẫn đảm bảo thứ tự vừa sắp xếp ở câu 4
//Sử dụng hai hàm insertTail && SapXep
//=================================================================================
//Câu 6:Xuất số gói hàng cần gởi của từng khu vực tỉnh thành
void XuatGoiHangTheoTinhThanh(Slist sl);
//=================================================================================
//Câu 7:Xuất khách hàng thân thiết, là những khách hàng có tổng chi phí gởi hàng nhiều nhất.
void XuatKhachHangThanThiet(Slist sl);
//=================================================================================
//Câu 8:Cho biết ông Le Anh có bao nhiêu gói hàng gởi đi, và bao nhiêu gói nhận về.
void DonHangLeAnh(Slist sl);
//=================================================================================
//Câu 9:Khách thường gởi loại hàng nào nhiều nhất?
void XuatLoaiHangNhieuNhat(Slist sl);
//=================================================================================
//Câu 10:Xuất thông tin các gói hàng có phí chuyển cao nhất.
void XuatGoiHangCoPhiCaoNhat(Slist sl);
//=================================================================================

//=================================================================================
//Phần hàm MAIN
//=================================================================================
int main() //main
{
	int DemTam = 0; //bien dem tam
	Menu(DemTam);
	return 0;
}
//=================================================================================
//Phần định nghĩa hàm
//=================================================================================

SNode* createSNode(Itemtype x) //Khoi tao 1 node
{
	SNode* p = new SNode; //Cap phat bo nho cho node
	if (p == NULL) //Kiem tra xem co du bo nho de cap phat khong
	{
		printf("Khong du bo nho cap phat"); //Neu khong du bo nho de cap phat thi thong bao
		return NULL; //Tra ve NULL
	}
	p->Info = x; //Gan gia tri cho node
	p->Next = NULL; //Gan next cua node la NULL
	return p; //Tra ve node
}
//=================================================================================
void initSList(Slist &sl) //Khoi tao danh sach lien ket don
{
	sl.Head = NULL; //Gan head cua danh sach la NULL
	sl.Tail = NULL; //Gan tail cua danh sach la NULL
}
//=================================================================================
int isEmpty(Slist sl) //Kiem tra danh sach lien ket don co rong hay khong
{
	if (sl.Head == NULL) //Neu head cua danh sach la NULL thi danh sach rong
		return 1;
	return 0;
}
//=================================================================================

void showSNode(SNode* p) //Hien thi 1 node
{
	Itemtype ThongTin = p->Info; //Khai bao 1 bien kieu Itemtype va gan gia tri cho bien do bang gia tri cua node
	printf("%-10s\t% -25s%-20s%-20s%-20s%-25s%-20s%-17.3f%-15.1f%-10s%\n\n", ThongTin.MaSoHangHoa, ThongTin.TenNguoiGui,
		ThongTin.DiaChiNguoiGui, ThongTin.SoDienThoaiNguoiGui, ThongTin.TenNguoiNhan, ThongTin.DiaChiNguoiNhan, ThongTin.SoDienThoaiNguoiNhan,
		ThongTin.PhiChuyenHang, ThongTin.TrongLuong, ThongTin.LoaiHang);
}
//=================================================================================
void showSlist(Slist sl) //Hien thi danh sach lien ket don
{
	int a = 1; //Khai bao bien n va a
	if (isEmpty(sl) == 1)
	{
		printf("Khong co bat ky thong tin nao\n");//Neu danh sach rong thi thong bao
		return;
	}
	SNode*p = sl.Head; //Khai bao 1 bien p va gan gia tri cho bien do bang head cua danh sach
	printf("Thong Tin Khach Hang:\n");
	printf("Ma So Hang Hoa \tTen Nguoi Gui \t\t Dia Chi Nguoi Gui   SDT Nguoi Gui\t Ten Nguoi Nhan");
	printf("      Dia Chi Nguoi Nhan       SDT Nguoi Nhan      Phi Chuyen Hang  Trong Luong\n");
	while (p != NULL) //Lap den khi p bang NULL
	{
		showSNode(p); //Hien thi node
		p = p->Next; //Gan gia tri cho p bang next cua p
		a++; //Tang bien a len 1 don vi
	}
}
//=================================================================================
int insertHead(Slist &sl, SNode *p) //Chen 1 node vao dau danh sach lien ket don
{

	if (p == NULL) //Kiem tra xem co du bo nho de cap phat khong
		return 0; //Neu khong du bo nho de cap phat thi tra ve 0
	if (isEmpty(sl) == 1) //Neu danh sach rong
	{
		sl.Head = p; //Gan head cua danh sach bang p
		sl.Tail = p; //Gan tail cua danh sach bang p
	}
	else
	{
		p->Next = sl.Head; //Gan next cua p bang head cua danh sach
		sl.Head = p; //Gan head cua danh sach bang p
	}
	return 1;
}
//=================================================================================
int insertTail(Slist &sl, SNode* p) //Chen 1 node vao cuoi danh sach lien ket don
{
	if (p == NULL) //Kiem tra xem co du bo nho de cap phat khong
		return 0; //Tra ve 0
	if (isEmpty(sl) == 1) //Neu danh sach rong
	{
		sl.Head = p; //Gan head cua danh sach bang p
		sl.Tail = p; //Gan tail cua danh sach bang p
	}
	else
	{
		sl.Tail->Next = p; //Gan next cua tail cua danh sach bang p
		sl.Tail = p; //Gan tail cua danh sach bang p
	}
	return 1;
}
//=================================================================================
void DoiKyTu(char a[50])
{
	int b;
	b = strlen(a);
	if (islower(a[0]))
		a[0] = a[0] - 32;
	for (int i = 0; i < b; i++)
	if (isspace(a[i]))
	{
		if (islower(a[i + 1]))
			a[i + 1] = a[i + 1] - 32;
	}
	else if (isupper(a[i + 1]))
		a[i + 1] = a[i + 1] + 32;
}
//================================================================================
void XoaKhoangTrang(char a[50])
{
	int i = 0, c = 0, h = 0;
	while (isspace(a[i]))
	{
		if (a[i] == ' ')
			c++;
		i++;
	}
	if (a[0] == ' ')
	{
		memmove(a, a + c, strlen(a));
	}
}
//=================================================================================
SNode *NhapThongTin() //Ham nhap thong tin
{
	Itemtype ThongTin; //Khai bao 1 bien kieu Itemtype
	printf("\tNhap Ma So Hang Hoa:"); //Thong bao
	gets(ThongTin.MaSoHangHoa); //Nhap ma so hang hoa
	XoaKhoangTrang(ThongTin.MaSoHangHoa);
	printf("\tNhap Ten Nguoi Gui:");
	gets(ThongTin.TenNguoiGui); //Nhap ten nguoi gui
	DoiKyTu(ThongTin.TenNguoiGui);
	XoaKhoangTrang(ThongTin.TenNguoiGui);
	printf("\tNhap Dia Chi Nguoi Gui:");
	gets(ThongTin.DiaChiNguoiGui); //Nhap dia chi nguoi gui
	DoiKyTu(ThongTin.DiaChiNguoiGui);
	XoaKhoangTrang(ThongTin.DiaChiNguoiGui);
	printf("\tNhap So Dien Thoai Nguoi Gui:");
	gets(ThongTin.SoDienThoaiNguoiGui); //Nhap so dien thoai nguoi gui	
	XoaKhoangTrang(ThongTin.SoDienThoaiNguoiGui);
	printf("\tNhap Ten Nguoi Nhan:");
	gets(ThongTin.TenNguoiNhan); //Nhap ten nguoi nhan
	DoiKyTu(ThongTin.TenNguoiNhan);
	XoaKhoangTrang(ThongTin.TenNguoiNhan);
	printf("\tNhap Dia Chi Nguoi Nhan:");
	gets(ThongTin.DiaChiNguoiNhan); //Nhap dia chi nguoi nhan
	DoiKyTu(ThongTin.DiaChiNguoiNhan);
	XoaKhoangTrang(ThongTin.DiaChiNguoiNhan);
	printf("\tNhap So Dien Thoai Nguoi Nhan:");
	gets(ThongTin.SoDienThoaiNguoiNhan); //Nhap so dien thoai nguoi nhan
	XoaKhoangTrang(ThongTin.SoDienThoaiNguoiNhan);
	do{
		printf("\tNhap Phi Chuyen Hang (1DV = 1000VND):");
		scanf("%f", &ThongTin.PhiChuyenHang); //Nhap phi chuyen hang
		if (ThongTin.PhiChuyenHang < 0)
			printf("Gia tri khong hop le!");
	} while (ThongTin.PhiChuyenHang < 0);
	do{
		printf("\tNhap Trong Luong(1DV = 1KG):");
		scanf("%f", &ThongTin.TrongLuong); //Nhap trong luong
		if (ThongTin.TrongLuong < 0)
			printf("Gia tri khong hop le!");
	} while (ThongTin.TrongLuong < 0);
	while (getchar() != '\n'); //Xoa bo nho dem
	printf("\tNhap Loai Hang:\n");
	printf("\t1.Kho\n");
	printf("\t2.Long\n");
	printf("\t3.DeVo\n");
	printf("\t4.KhongDuocDeThamNuoc\n");
	printf("\t  Nhap cac lua chon tren: ");
	int x;
	do
	{
		scanf("%d", &x);
		if ((x > 4) || (x <= 0))
			printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai:");
		else
		{
			switch (x)
			{
			case 1: //Neu x bang 1
			{
						char kho[] = "Loai Hang: Kho"; //Khai bao 1 bien kho va gan gia tri cho bien do
						strcpy(ThongTin.LoaiHang, kho); //Sao chep gia tri cua bien kho sang bien LoaiHang
						break;
			}
			case 2: //Neu x bang 2
			{
						char ChatLong[] = "Loai Hang: Long"; //Khai bao 1 bien ChatLong va gan gia tri cho bien do
						strcpy(ThongTin.LoaiHang, ChatLong); //Sao chep gia tri cua bien ChatLong sang bien LoaiHang
						break;
			}
			case 3: //Neu x bang 3
			{
						char DeVo[] = "Loai Hang: De Vo"; //Khai bao 1 bien DeVo va gan gia tri cho bien do
						strcpy(ThongTin.LoaiHang, DeVo); //Sao chep gia tri cua bien DeVo sang bien LoaiHang
						break;
			}
			case 4: //Neu x bang 4
			{
						char KhongDuocDeThamNuoc[] = "Loai Hang: Khong Duoc De Tham Nuoc"; //Khai bao 1 bien KhongDuocDeThamNuoc va gan gia tri cho bien do
						strcpy(ThongTin.LoaiHang, KhongDuocDeThamNuoc); //Sao chep gia tri cua bien KhongDuocDeThamNuoc sang bien LoaiHang
						break;
			}
			}
		}
	} while ((x > 4) || (x <= 0)); //Lap den khi nhap dung gia tri
	SNode* p = createSNode(ThongTin); //Khai bao 1 bien p va gan gia tri cho bien do
	return p;
}
//=================================================================================
void createSlist(Slist &sl) //Ham khoi tao danh sach lien ket don
{
	int n, a = 1;
	printf("Nhap So Luong Hang Hoa:");
	scanf("%d", &n);
	while (getchar() != '\n'); //Xoa bo nho dem
	initSList(sl); //Khoi tao danh sach lien ket don
	for (int i = 0; i < n; i++) //Lap n lan
	{
		printf("Nhap Thong Tin Hang Hoa,STT %d :\n", a);
		printf("\t================= STT %d =================\n", a);
		SNode* p = NhapThongTin(); //Khai bao 1 bien p va gan gia tri cho bien do
		insertTail(sl, p); //Chen p vao cuoi danh sach
		printf("\t==========================================\n");
		getchar(); //Xoa bo nho dem
		a++;
	}
}
//=================================================================================
void insertMid(Slist &sl, int g) //Ham them 1 phan tu vao giua danh sach
{
	int n;
	if (g < 2) //Neu g be hon 2
	{
		printf("Khong the thuc hien them giua!\n");
		return;
	}
	printf("\t===========================================\n");
	getchar(); //Xoa bo nho dem
	SNode*a = NhapThongTin(); //Khai bao 1 bien a va gan gia tri cho bien do
	SNode *b = NULL; //Khai bao 1 bien b va gan gia tri cho bien do
	SNode*p = sl.Head; //Khai bao 1 bien p va gan gia tri cho bien do
	do{
		printf("(Luu y danh sach hien co %d goi hang)\n", g);
		printf("Nhap vi tri ban muon them vao : ");
		scanf("%d", &n);
		if (n <= 1 || n > g)//Kiem tra vi tri muon them vao
			printf("Gia tri Khong hop le!");
	} while (n <= 1 || n > g);
	if (n == 2) //Neu n bang 2
	{
		a->Next = sl.Head->Next; //Gan gia tri cho bien a
		sl.Head->Next = a; //Gan gia tri cho bien sl.Head
		return;
	}
	for (int i = 1; i < (n - 1); i++)
	{
		b = p->Next; //Gan gia tri cho bien b
		p = p->Next; //Gan gia tri cho bien p 
	}
	if (a == NULL || b == NULL)
	{
		return;
	}

	else //Neu khong
	{
		a->Next = b->Next; //Gan gia tri cho bien a
		b->Next = a; //Gan gia tri cho bien b
	}
	return;

	printf("\t==========================================\n");
	getchar(); //Xoa bo nho dem
	a++;
}
//=================================================================================
void ReadFile(Slist &sl) // doc file
{
	FILE* f = fopen("100_GoiHang.txt", "r"); // mo file
	if (f == NULL) // kiem tra file co mo duoc khong
	{
		printf("Khong mo duoc file!\n");
		return;
	}
	Itemtype x; // khai bao bien x
	while (!feof(f)) // kiem tra file co het khong
	{
		fscanf(f, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%f,%f,%[^\n]\n", x.MaSoHangHoa, x.TenNguoiGui, x.DiaChiNguoiGui, x.SoDienThoaiNguoiGui, x.TenNguoiNhan, x.DiaChiNguoiNhan, x.SoDienThoaiNguoiNhan, &x.TrongLuong, &x.PhiChuyenHang, x.LoaiHang); // doc file
		SNode* p = createSNode(x); // tao 1 node moi
		insertTail(sl, p); // chen node vao cuoi danh sach
	}
	printf("Doc File Thanh Cong\n");
	fclose(f); //dong file
}
//=================================================================================
void WriteFile(Slist sl) // ghi file
{
	FILE* f = fopen("OutPutThongTinGoiHang.txt", "w"); // mo file
	if (f == NULL) // kiem tra file co mo duoc khong
	{
		printf("Khong mo duoc file\n");
		return;
	}
	SNode* p = sl.Head;
	while (p != NULL)
	{
		fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%.1f,%.3f,%s\n\n", p->Info.MaSoHangHoa, p->Info.TenNguoiGui
			, p->Info.DiaChiNguoiGui, p->Info.SoDienThoaiNguoiGui, p->Info.TenNguoiNhan, p->Info.DiaChiNguoiNhan, p->Info.SoDienThoaiNguoiNhan, p->Info.TrongLuong, p->Info.PhiChuyenHang, p->Info.LoaiHang);
		p = p->Next;
	}
	fclose(f);
}
//=================================================================================
int deleteHead(Slist &sl) //xoa node dau
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return 0;
	}
	SNode* p = sl.Head;
	sl.Head = sl.Head->Next;
	if (sl.Head == NULL)
		sl.Tail = NULL;
	delete p;
	return 1;
}
//=================================================================================
int deleteTail(Slist &sl) //xoa node cuoi
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return 0;
	}
	SNode *p = sl.Tail;
	SNode *q = sl.Head;
	if (p == q)
	{
		sl.Head = sl.Tail = NULL; //danh sach rong
	}
	else
	{
		while (q->Next != p) //duyet den node truoc node cuoi
			q = q->Next; //duyet den node truoc node cuoi
		sl.Tail = q; //cap nhat lai sl.Tail
		sl.Tail->Next = NULL;
	}
	delete p;
	return 1;
}
//=================================================================================
int DemSNode(Slist sl, int &g) //dem so node
{
	if (isEmpty(sl) == 1) //kiem tra danh sach co rong khong
	{
		return 0; //neu rong thi tra ve 0
	}
	else //neu khong rong
	{
		SNode* p = sl.Head; //khai bao 1 bien p va gan gia tri cho bien do
		while (p != NULL) //lap den khi p bang NULL
		{
			p = p->Next; //gan gia tri cho bien p
			g++; //tang bien g len 1
		}
	}
	return 1;
}
//=================================================================================
void deleteMid(Slist &sl, int g) //xoa node giua
{
	int n;
	if (g <= 2)
	{
		printf("=> Khong the thuc hien chuc nang nay\n"); //thong bao khong the thuc hien xoa giua
		return; //tra ve
	}
	else //neu khong
	{
		SNode*p, *q; //khai bao 2 bien p va q
		SNode*a = sl.Head; //khai bao 1 bien a va gan gia tri cho bien do
		do{
			printf("(Luu y danh sach hien co %d goi hang)\n", g);
			printf("Nhap vi tri ban muon xoa : ");
			scanf("%d", &n);
			if (n <= 1 || n >= g)
				printf("Gia tri Khong hop le!");
		} while (n <= 1 || n >= g);
		if (n == 2) //neu n bang 2
		{
			p = sl.Head->Next; //gan gia tri cho bien p
			sl.Head->Next = p->Next; //gan gia tri cho bien sl.Head->Next
			delete p;
			return;
		}
		for (int i = 1; i < (n - 1); i++)
		{
			q = a->Next; //gan gia tri cho bien q
			a = a->Next;
		}
		if ((q == NULL) || q->Next == NULL) //neu q bang NULL hoac q->Next bang NULL
			return;
		p = q->Next; //gan gia tri cho bien p
		q->Next = p->Next; //gan gia tri cho bien q->Next
		if (sl.Tail = p) //neu sl.Tail bang p
			sl.Tail = q; //gan gia tri cho bien sl.Tail
		delete p; //giai phong bo nho
		return;
	}
}
//=================================================================================
void XuatKhachHangThanThiet(Slist sl)
{
	if (isEmpty(sl) == 1)
		return;

	// Khởi tạo mảng lưu tổng số tiền vận chuyển của từng người gửi
	float tongTienVanChuyen[50] = { 0 };

	// Duyệt danh sách liên kết đơn hàng để tính tổng số tiền vận chuyển của mỗi người gửi
	SNode* p = sl.Head;
	while (p != NULL)
	{
		int viTri = -1;
		for (int i = 0; i < 50; i++) // Duyệt qua từng phần tử của mảng
		{
			if (strcmp(p->Info.TenNguoiGui, "") == 0)
				break;

			if (strcmp(p->Info.TenNguoiGui, sl.Head->Info.TenNguoiGui) == 0)
			{
				viTri = 0;
				break;
			}
			else if (strcmp(p->Info.TenNguoiGui, sl.Head->Next->Info.TenNguoiGui) == 0)
			{
				viTri = 1;
				break;
			}
			else if (strcmp(p->Info.TenNguoiGui, sl.Head->Next->Next->Info.TenNguoiGui) == 0)
			{
				viTri = 2;
				break;
			}
			else if (strcmp(p->Info.TenNguoiGui, sl.Head->Next->Next->Next->Info.TenNguoiGui) == 0)
			{
				viTri = 3;
				break;
			}
		}

		if (viTri >= 0 && viTri < 50) // Kiểm tra xem viTri có hợp lệ hay không
		{
			tongTienVanChuyen[viTri] += p->Info.PhiChuyenHang;
		}

		p = p->Next;
	}

	float tongTienVanChuyenCaoNhat = 0;
	for (int i = 0; i < 50; i++)
	{
		if (tongTienVanChuyen[i] > tongTienVanChuyenCaoNhat)
		{
			tongTienVanChuyenCaoNhat = tongTienVanChuyen[i];
		}
	}
	printf("Voi Tong So Tien Van Chuyen:%.3f\n", tongTienVanChuyenCaoNhat);
	printf("Cac nguoi gui co tong so tien van chuyen cao nhat la: \n");
	for (int i = 0; i < 50; i++)
	{
		if (tongTienVanChuyen[i] == tongTienVanChuyenCaoNhat)
		{
			if (i == 0)
			{
				printf("%s \n", sl.Head->Info.TenNguoiGui);
			}
			else if (i == 1)
			{
				printf("%s \n", sl.Head->Next->Info.TenNguoiGui);
			}
			else if (i == 2)
			{
				printf("%s \n", sl.Head->Next->Next->Info.TenNguoiGui);
			}
			else if (i == 3)
			{
				printf("%s \n", sl.Head->Next->Next->Next->Info.TenNguoiGui);
			}
		}
	}
}
//=================================================================================
void SapXep(Slist sl) // Hàm sắp xếp danh sách liên kết đơn theo địa chỉ người nhận và loại hàng
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return;
	}
	Itemtype temp; // Khai báo biến temp kiểu Itemtype
	for (SNode *i = sl.Head; i != NULL; i = i->Next) // Duyệt qua từng đơn hàng
	{

		for (SNode *j = i->Next; j != NULL; j = j->Next) // Duyệt qua từng đơn hàng tiếp theo
		{
			if (strcmp(i->Info.DiaChiNguoiNhan, j->Info.DiaChiNguoiNhan) > 0 ||
				(strcmp(i->Info.DiaChiNguoiNhan, j->Info.DiaChiNguoiNhan) == 0 && strcmp(i->Info.LoaiHang, j->Info.LoaiHang) > 0)) // Nếu địa chỉ người nhận của đơn hàng i lớn hơn địa chỉ người nhận của đơn hàng j hoặc địa chỉ người nhận của đơn hàng i bằng địa chỉ người nhận của đơn hàng j và loại hàng của đơn hàng i bằng loại hàng của đơn hàng j
			{
				temp = i->Info; // Gán temp = i->Info
				i->Info = j->Info; // Gán i->Info = g->Info
				j->Info = temp; // Gán g->Info = temp
			}
		}
	}
}
//=================================================================================
void XuatLoaiHangNhieuNhat(Slist sl) // Hàm tìm ra loại hàng có nhiều đơn hàng nhất
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return;
	}
	int a[4] = { 0, 0, 0, 0 }; // Khai báo mảng a có 4 phần tử
	int Kho = 0; // Khởi tạo biến Kho = 0
	int Long = 0; // Khởi tạo biến Long = 0
	int DeVo = 0; // Khởi tạo biến DeVo = 0
	int	KhongDuocDeThamNuoc = 0; // Khởi tạo biến KhongDuocDeThamNuoc = 0
	int temp = 0; // Khởi tạo biến temp = 0
	for (SNode* i = sl.Head; i != NULL; i = i->Next) // Duyệt qua từng đơn hàng
	{
		if (strcmp(i->Info.LoaiHang, "Loai Hang: Kho") == 0) // Nếu loại hàng của đơn hàng i bằng "Loai Hang: Kho"
		{
			Kho++; // Tăng biến Kho lên 1
			a[0] = Kho; // Gán a[0] = Kho
		}
		else if (strcmp(i->Info.LoaiHang, "Loai Hang: Long") == 0) // Nếu loại hàng của đơn hàng i bằng "Loai Hang: Long"
		{
			Long++; // Tăng biến Long lên 1
			a[1] = Long; // Gán a[1] = Long
		}
		else if (strcmp(i->Info.LoaiHang, "Loai Hang: De Vo") == 0) // Nếu loại hàng của đơn hàng i bằng "Loai Hang: De Vo"
		{
			DeVo++; // Tăng biến DeVo lên 1
			a[2] = DeVo; // Gán a[2] = DeVo
		}
		else if (strcmp(i->Info.LoaiHang, "Loai Hang: Khong Duoc De Tham Nuoc") == 0) // Nếu loại hàng của đơn hàng i bằng "Loai Hang: Khong Duoc De Tham Nuoc"
		{
			KhongDuocDeThamNuoc++; // Tăng biến KhongDuocDeThamNuoc lên 1
			a[3] = KhongDuocDeThamNuoc; // Gán a[3] = KhongDuocDeThamNuoc
		}
	}
	temp = a[0]; // Gán temp = a[0]
	for (int i = 0; i < 4; i++) // Duyệt qua từng phần tử của mảng a
	{
		if (a[i]>temp) // Nếu a[i] lớn hơn temp
			temp = a[i]; // Gán temp = a[i]
	}
	printf("Voi So Luong Loai Hang:%d\n", temp);
	if (Kho == temp) // Nếu Kho bằng temp
		printf("Loai Hang Nhieu Nhat La: Kho\n");
	if (Long == temp) // Nếu Long bằng temp
		printf("Loai Hang Nhieu Nhat La: Long\n");
	if (DeVo == temp) // Nếu DeVo bằng temp
		printf("Loai Hang Nhieu Nhat La: De Vo\n");
	if (KhongDuocDeThamNuoc == temp) // Nếu KhongDuocDeThamNuoc bằng temp
		printf("Loai Hang Nhieu Nhat La: Khong Duoc De Tham Nuoc\n");
}
//=================================================================================
void XuatGoiHangCoPhiCaoNhat(Slist sl) // Hàm xuất ra các đơn hàng có phí chuyển hàng cao nhất
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return;
	}
	float temp = sl.Head->Info.PhiChuyenHang; // Khởi tạo biến temp = phí chuyển hàng của đơn hàng đầu tiên
	for (SNode *i = sl.Head; i != NULL; i = i->Next) // Duyệt qua từng đơn hàng
	{
		if (i->Info.PhiChuyenHang > temp) // Nếu phí chuyển hàng của đơn hàng i lớn hơn temp
		{
			temp = i->Info.PhiChuyenHang; // Gán temp = phí chuyển hàng của đơn hàng i
		}
	}
	for (SNode *i = sl.Head; i != NULL; i = i->Next) // Duyệt qua từng đơn hàng
	{
		if (i->Info.PhiChuyenHang == temp) // Nếu phí chuyển hàng của đơn hàng i bằng temp
		{
			printf("Thong Tin Khach Hang:\n");
			printf("Ma So Hang Hoa \tTen Nguoi Gui \t\t Dia Chi Nguoi Gui   SDT Nguoi Gui\t Ten Nguoi Nhan");
			printf("      Dia Chi Nguoi Nhan       SDT Nguoi Nhan      Phi Chuyen Hang  Trong Luong\n");
			showSNode(i); // Gọi hàm showSNode(i) để xuất ra đơn hàng i
		}
	}
}
//=================================================================================
void DonHangLeAnh(Slist sl) // Hàm xuất ra số đơn hàng mà Le Anh gửi đi và nhận về
{
	if (isEmpty(sl) == 1)
	{
		printf("Danh Sach Hien Dang Rong! \n => Khong the thuc hien chuc nang nay\n");
		return;
	}
	int DemGoiHangGoi = 0, DemGoiHangNhan = 0; // Khởi tạo biến DemGoiHangGoi = 0 và biến DemGoiHangNhan = 0
	char sosanh[15] = "Le Anh"; // Khởi tạo biến sosanh có giá trị là "Le Anh"
	for (SNode* p = sl.Head; p != NULL; p = p->Next) // Duyệt qua từng đơn hàng
	{
		if (strcmp(p->Info.TenNguoiGui, sosanh) == 0) // Nếu tên người gửi của đơn hàng p bằng "Le Anh"
		{
			DemGoiHangGoi++; // Tăng biến DemGoiHangGoi lên 1
		}
		if (strcmp(p->Info.TenNguoiNhan, sosanh) == 0) // Nếu tên người nhận của đơn hàng p bằng "Le Anh"
		{
			DemGoiHangNhan++; // Tăng biến DemGoiHangNhan lên 1
		}
	}
	printf("so hang ma Le Anh gui di la : %d\n", DemGoiHangGoi); // Xuất ra số đơn hàng mà Le Anh gửi đi
	printf("so hang ma Le Anh nhan ve la : %d\n", DemGoiHangNhan); // Xuất ra số đơn hàng mà Le Anh nhận về

}
//=================================================================================
void XuatGoiHangTheoTinhThanh(Slist sl) // Hàm xuất ra số đơn hàng mà mỗi khu vực/tỉnh thành gửi đi
{
	SNode *p = sl.Head; // Khởi tạo biến p = đơn hàng đầu tiên
	while (p != NULL)  // Duyệt qua từng đơn hàng
	{
		char *KhuVucTinhThanh = p->Info.DiaChiNguoiNhan; // Khởi tạo biến KhuVUcTinhThanh = địa chỉ người nhận của đơn hàng  
		int dem = 0; // Khởi tạo biến dem = 0
		while (p != NULL && strcmp(p->Info.DiaChiNguoiNhan, KhuVucTinhThanh) == 0) // Nếu địa chỉ người nhận của đơn hàng p bằng KhuVucTinhThanh
		{
			dem++; // Tăng biến dem lên 1
			p = p->Next; // Gán p = đơn hàng tiếp theo
		}
		printf("Khu vuc/tinh thanh: %s, So goi hang can gui: %d\n", KhuVucTinhThanh, dem); // Xuất ra khu vực/tỉnh thành và số đơn hàng cần gửi
	}
}
//=================================================================================
void Menu(int DemTam)
{
	DemTam = 0;
	Slist ds;//khai bao danh sach
	initSList(ds);
	int x;
	do //vong lap do while
	{
		printf("\t================== MENU ==================\n");
		printf("\t1-Nhap Thong Tin Goi Hang:\n");
		printf("\t2-Them Thong Tin Goi Hang:\n");
		printf("\t3-Xoa Thong Tin Goi Hang:\n");
		printf("\t4-Sap Xep Thong Tin Goi Hang:\n");
		printf("\t5-Xuat Thong Tin Goi Hang:\n");
		printf("\t6-Luu Thong Tin Goi Hang Vao File:\n");
		printf("\t0-Thoat:\n");
		printf("\t==========================================\n");
		printf("\t  Nhap cac lua chon tren: ");
		scanf(" %d", &x);
		if ((x<0) || (x>6)) //kiem tra gia tri nhap vao
			printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai!\n"); //thong bao loi
		else //neu gia tri nhap vao hop le
		{
			switch (x) //switch case
			{
			case 1: //neu gia tri nhap vao la 1
			{
						int n;
						printf("Chon Cac Phuong Thuc Nhap Sau:\n"); //thong bao
						printf("1.Nhap Tu Ban Phim\n");
						printf("2.Doc File\n");
						printf("Nhap cac lua chon tren: ");
						do{
							scanf("%d", &n); //nhap gia tri
							if ((n<1) || (n>2)) //kiem tra gia tri nhap vao
								printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai:");
						} while ((n < 1) || (n > 2));//thong bao loi
						if (n == 1) //neu gia tri nhap vao la 1
						{
							createSlist(ds); //tao danh sach
						}
						else if (n == 2) //neu gia tri nhap vao la 2
						{
							initSList(ds); //khoi tao danh sach
							ReadFile(ds); //doc file
						}
						break;
			}
			case 2: //neu gia tri nhap vao la 2
			{
						int n;
						printf("Chon Cac Phuong Thuc Them Thong Tin Goi Hang Sau:\n");
						printf("1.Them Them Thong Tin Goi Hang Vao Dau Danh sach\n");
						printf("2.Them Them Thong Tin Goi Hang Vao Giua Danh Sach\n");
						printf("3.Them Them Thong Tin Goi Hang Vao Cuoi Danh Sach\n");
						printf("4.Them Them Thong Tin Goi Hang && Xap Sep Theo Tinh Thanh\n");
						printf("Nhap cac lua chon tren: ");
						do{
							scanf("%d", &n); //nhap gia tri
							if ((n<1) || (n>4)) //kiem tra gia tri nhap vao
								printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai:");
						} while ((n < 1) || (n > 4));//thong bao loi
						if (n == 1) //neu gia tri nhap vao la 1
						{
							printf("\t==========================================\n");
							getchar();//xoa bo nho dem
							SNode*p = NhapThongTin(); //nhap thong tin
							insertHead(ds, p); //them vao dau danh sach
							printf("Goi Hang Duoc Them Thanh Cong\n");
						}
						else if (n == 2) //neu gia tri nhap vao la 2
						{
							DemSNode(ds, DemTam); //dem so luong node
							insertMid(ds, DemTam); //them vao giua danh sach
							if (isEmpty(ds) == 0 && DemTam > 1) // in ra cau lenh khi danh sach khong rong
							{
								printf("Goi Hang Duoc Them Thanh Cong\n");
							}
							DemTam = 0;
						}
						else if (n == 3) //neu gia tri nhap vao la 3
						{
							printf("\t==========================================\n");
							getchar(); //xoa bo nho dem
							SNode*p = NhapThongTin(); //nhap thong tin
							insertTail(ds, p); //them vao cuoi danh sach
							printf("Goi Hang Duoc Them Thanh Cong\n");
						}
						else if (n == 4) //neu gia tri nhap vao la 4
						{
							printf("\t==========================================\n");
							getchar(); //xoa bo nho dem
							SNode*p = NhapThongTin(); //nhap thong tin
							insertTail(ds, p); //them vao cuoi danh sach
							SapXep(ds); //sap xep danh sach
							printf("Goi Hang Duoc Them Thanh Cong\n");
						}
						break;
			}
			case 3: //neu gia tri nhap vao la 3
			{
						int n;
						printf("Chon Cac Phuong Thuc Xoa Goi Hang Sau:\n");
						printf("1.Xoa Thong Tin Goi Hang Dau Danh sach\n");
						printf("2.Xoa Thong Tin Goi Hang Giua Danh Sach\n");
						printf("3.Xoa Thong Tin Goi Hang Cuoi Danh Sach\n");
						printf("Nhap cac lua chon tren: ");
						do{
							scanf("%d", &n); //nhap gia tri
							if ((n<1) || (n>3)) //kiem tra gia tri nhap vao
								printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai:");
						} while ((n < 1) || (n > 3));//thong bao loi
						if (n == 1) //neu gia tri nhap vao la 1
						{
							deleteHead(ds); //xoa dau danh sach
							if (isEmpty(ds) == 0)
							{
								printf("Xoa Thong Tin Goi Hang Thanh Cong\n");
							}
						}
						else if (n == 2) //neu gia tri nhap vao la 2
						{
							DemSNode(ds, DemTam); //dem so luong node
							deleteMid(ds, DemTam); //xoa giua danh sach
							if (isEmpty(ds) == 0 && DemTam > 2)
							{
								printf("Xoa Thong Tin Goi Hang Thanh Cong\n");
							}
							DemTam = 0;
						}
						else if (n == 3) //neu gia tri nhap vao la 3
						{
							deleteTail(ds); //xoa cuoi danh sach
							if (isEmpty(ds) == 0)
							{
								printf("Xoa Thong Tin Goi Hang Thanh Cong\n");
							}
						}
						break; //thoat khoi switch case
			}
			case 4: //neu gia tri nhap vao la 4
			{
						SapXep(ds); //sap xep danh sach
						if (isEmpty(ds) == 0)
						{
							printf("Thong Tin Goi Hang Da Duoc Sap Xep\n");
						}
						break; //thoat khoi switch case
			}
			case 5: //neu gia tri nhap vao la 5
			{
						int n;
						printf("Chon Cac Phuong Thuc Xuat Goi Hang Sau:\n");
						printf("1.Xuat Toan Bo Goi Hang Co Trong Danh Sach\n");
						printf("2.Xuat Loai Hang Khach Gui Nhieu Nhat\n");
						printf("3.Xuat Thong Tin Goi Hang Co Phi Van Chuyen Cao Nhat\n");
						printf("4.Xuat So Luong Goi Hang Nhan Va Gui Di Cua Ong Le Anh\n");
						printf("5.Xuat So Luong Goi Hang Theo Khu Vuc Tinh Thanh\n");
						printf("6.Xuat Khach Hang Than Thiet\n");
						printf("Nhap cac lua chon tren: ");
						do{
							scanf("%d", &n); //nhap gia tri
							if ((n<1) || (n>6)) //kiem tra gia tri nhap vao
								printf("Gia Tri Khong Hop Le,Vui Long Nhap Lai:");
						} while ((n < 1) || (n > 6));//thong bao loi
						if (n == 1) //neu gia tri nhap vao la 1
						{
							showSlist(ds); //xuat toan bo danh sach
						}
						else if (n == 2) //neu gia tri nhap vao la 2
						{
							XuatLoaiHangNhieuNhat(ds); //xuat loai hang khach gui nhieu nhat
						}
						else if (n == 3) //neu gia tri nhap vao la 3
						{
							XuatGoiHangCoPhiCaoNhat(ds); //xuat thong tin goi hang co phi van chuyen cao nhat
						}
						else if (n == 4) //neu gia tri nhap vao la 4
						{
							DonHangLeAnh(ds); //xuat so luong goi hang nhan va gui di cua ong le anh
						}
						else if (n == 5) //neu gia tri nhap vao la 5
						{
							SapXep(ds); //sap xep danh sach
							XuatGoiHangTheoTinhThanh(ds); //xuat so luong goi hang theo khu vuc tinh thanh
						}
						else if (n == 6) //neu gia tri nhap vao la 6
						{
							SapXep(ds); //sap xep danh sach
							XuatKhachHangThanThiet(ds); //xuat khach hang than thiet
						}
						break; //thoat khoi switch case
			}
			case 6: //neu gia tro nhap vao la 6
			{
						WriteFile(ds); //ghi file
						printf("Ghi File Thanh Cong\n"); //thong bao ghi file thanh cong
						break; //thoat khoi switch case
			}
			}
		}
	} while (x != 0); //lap lai neu gia tri nhap vao khac 0
}
//=================================================================================
//===================================+++END+++======================================
