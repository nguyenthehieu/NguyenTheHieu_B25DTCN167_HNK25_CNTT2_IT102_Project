#include<stdio.h>
#include<string.h>
#define MAX_Products 100
#define MAX_Transaction 200

struct Product{
	char productId[10];   // ma hang hoa
	char name[50];     // ten hang hoa
	char unit[10];   // don vi
	int qty;      // so luong ton kho
	int status;   //trang thai(1:còn sd, 0: het han)
};

struct Transaction{ //Xuat/nhap hÃ ng
	char transId[20]; // Ma giao dich (Sinh ngau nhien hoac tu tang).
	char productId[10]; // Ma hang hoa
	char type[5];  //Kieu xuat/nhap (IN = nhap/ OUT = xuat).
	char date[15]; // Thoi gian giao dich.
};

struct Product prd[MAX_Products];
struct Transaction trans[MAX_Transaction];
int productCount = 0; // dem so hang hoa
int transCount = 0;

//kiem tra du lieu
int isEmpty(char str[]) { // kiem tra chuoi rong
    return strlen(str) == 0;
}

int isDuplicateId(char id[]) { // kiem tra trung nhau
    for (int i = 0; i < productCount; i++) {
        if (strcmp(prd[i].productId, id) == 0)
            return 1;
    }
    return 0;
}

//1. THEM SAN PHAM
void addProduct() {
    int amount;
	printf("<<----- THEM SAN PHAM ----->>\n");
    printf("Nhap so luong san pham muon them: ");
    scanf("%d", &amount);
    getchar();

    if (productCount + amount > MAX_Products) {
        printf("Kho da day. Khong the them.\n");
        return;
    }

    for (int i = 0; i < amount; i++) {
        printf("\n<<--- San pham %d --->>\n", productCount + 1);

        do {
            printf("Nhap ma san pham: ");
            fgets(prd[productCount].productId, 10, stdin);
            prd[productCount].productId[strcspn(prd[productCount].productId, "\n")] = '\0';

            if (isEmpty(prd[productCount].productId))
                printf("ID khong duoc trong\n");
            else if (isDuplicateId(prd[productCount].productId))
                printf("ID da ton tai, nhap ID khac!\n");
            else break;

        } while (1);

        do {
            printf("Nhap ten san pham: ");
            fgets(prd[productCount].name, 50, stdin);
            prd[productCount].name[strcspn(prd[productCount].name, "\n")] = '\0';

            if (isEmpty(prd[productCount].name))
                printf("Ten khong duoc de trong!\n");

        } while (isEmpty(prd[productCount].name));
        
        do {
            printf("Nhap don vi tinh: ");
            fgets(prd[productCount].unit, 10, stdin);
            prd[productCount].unit[strcspn(prd[productCount].unit, "\n")] = '\0';

            if (isEmpty(prd[productCount].unit))
                printf("Don vi tinh khong duoc de trong!\n");

        } while (isEmpty(prd[productCount].unit));

        do {
            printf("Nhap so luong ton kho: ");
            scanf("%d", &prd[productCount].qty);
            getchar();
            
            if (prd[productCount].qty < 0)
                printf("So luong phai >= 0!\n");

        } while (prd[productCount].qty < 0);

        printf("Trang thai (1: con sd, 0: het han): ");
        scanf("%d", &prd[productCount].status);
        getchar();

        productCount++;
    }

    printf("<<--- Them san pham thanh cong. --->>\n");
}

//2. CAP NHAT SAN PHAM
void updateProduct() {
	char id[10];
	printf("Nhap ma san pham can cap nhat: ");
	fgets(id,10,stdin);
	id[strcspn(id,"\n")]='\0';
	int found = -1;
	
	for(int i=0; i<productCount; i++){    //tim ID
		if( strcmp(id, prd[i].productId) == 0){
			found = i;
			break;
		}
	}	
	if (found == -1){
		printf("Khong tim thay.\n");
		return;
	}
	printf("<<--- CAP NHAT SAN PHAM --->>\n");
	
	printf("Nhap ten moi: ");
	char newName[50];
	fgets(newName, 50, stdin);
	newName[strcspn(newName, "\n")] = '\0';
	if(!isEmpty(newName))
		strcpy(prd[found].name, newName);
		
	printf("Nhap don vi moi: ");
	char newUnit[10];
	fgets(newUnit, 10, stdin);
	newUnit[strcspn(newUnit, "\n")] ='\0';
	if(!isEmpty(newUnit))
		strcpy(prd[found].unit, newUnit);
		
	printf("Nhap so luong moi: ");
	int newQty;
	scanf("%d",&newQty);
	getchar();
	if(newQty>=0)
		prd[found].qty = newQty;
		
	printf("Nhap trang thai moi (1-Con su dung, 0-Het han): ");
	int newStatus;
	scanf("%d",&newStatus);
	getchar();
	prd[found].status = newStatus;
	
	printf("<<---Cap nhat thanh cong--->>\n");
	}


int main (){
	int choice;

	while(1){
	printf("+----------QUAN LY HANG HOA----------+\n");
	printf("1. Them ma hang moi.     	 	    \n");
	printf("2. Cap nhat thong tin.              \n");
	printf("3. Quan ly trang thai (Khoa/Xoa).   \n");
	printf("4. Tra cuu san pham.                \n");
	printf("5. Dang sach (Phan trang).          \n");
	printf("6. Sap xep danh sach.              \n");
	printf("7. Giao dich xuat/nhap hang hoa.    \n");
	printf("8. Lich su xuat/nhap.               \n");
	printf("+------------------------------------+\n");

	printf("Moi ban nhap lua chon: ");
	scanf("%d",&choice);

	switch(choice){
		case 1:
			addProduct();
			break;
		case 2:
			updateProduct();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;

		default:
			printf("Lua chon khong hop le. \n");
			return 0;
	}
	}
	return 0;
}
