#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Luu gia tri bang #define
#define MAX_ROW 9
#define MAX_COLUMN 9
#define MAX 10

//Tao cac cau truc va bien cuc bo theo mau
typedef struct POINT {
    int row;
    int column;
    int value;
    bool visited;
    struct POINT *prev;
} point_t;

typedef struct
{
    point_t data[MAX];
    int front;
    int rear;
}Queue;
point_t matrix[MAX_ROW][MAX_COLUMN];
bool checkCoordinate(int x, int y);
int findSurroundingPoint(int x, int y, point_t surroundingPnt[]);
void findShortestPath (int x, int y);
//Khoi tao ham doi
void initQueue(Queue *q)
{
       q->front = 0;    //He so dau cua hang
       q->rear = -1;    //He so cuoi cua hang
}
//Kiem tra hang rong
int isEmpty(Queue q)
{
       return (q.rear < q.front);   //Khi front>rear -> hang rong
}
//Kiem tra ham day
int isFull(Queue q)
{
    //Neu rear == MAX-1 -> ham da day
    if(q.rear == MAX - 1) {
        return 1;
    }
       else return 0;
}
//Cho them 1 phan tu vao hang
void enQueue(Queue *q, point_t x)
{
    //Neu hang chua day -> them 1 phan tu vao mang data + tang 1 gia tri cho rear
      if (!isFull(*q)) {

            q->rear = q->rear + 1;
            q->data[q->rear] = x;
       }
       //Neu mang da day
       if(q->rear == MAX - 1)
        {
            //Bo nhung phan tu ma front da di qua
                  for(int i = q->front; i <= q->rear; i++){
                           q->data[i - q->front] = q->data[i];
                  }
                  q->rear = MAX - q->front;
                  q->front = 0;
        }
}
//Lay phan tu dau tien cua hang
point_t deQueue(Queue *q) {
    point_t d;
    //Neu ham khong rong
    if (!isEmpty(*q)) {
       d = q->data[q->front];
       q->front = q->front +1;
       //tang front len 1 va chuyen du lieu cho bien d
    }
    //Neu hang rong
    if (q->front > q->rear) {
        initQueue(q);
        //Dat lai front va rear
    };
    return d;
}


int main()
{
//Luu ma tran da cho truoc vao mang matrix
int array[]=
    {1,0,0,0,1,0,1,1,0,
     1,1,0,1,1,1,0,0,1,
     0,1,0,1,1,0,1,0,1,
     0,1,1,0,0,1,0,1,1,
     0,0,1,0,1,0,1,0,0,
     1,1,1,0,0,0,0,1,1,
     1,0,1,1,1,1,1,0,0,
     1,1,1,0,0,0,1,0,1,
     0,0,0,1,1,1,1,1,0};
// Su dung 2 loop de luu vao mang 2 chieu
for(int i=0,e=0;i<MAX_ROW;i++)
{
    for(int j=0;j<MAX_COLUMN;j++)
    {
        matrix[i][j].value=array[e];
        matrix[i][j].column=j;
        matrix[i][j].row=i;
        matrix[i][j].visited=false;
        e++;
    }
}
//Tuong tu gia tri cua tung phan tu trong mang
for(int i=0;i<MAX_ROW;i++)
{
    for(int j=0;j<MAX_COLUMN;j++)
    {
        printf("%d ",matrix[i][j].value);
    }
        printf("\n");
}

int x,y;    //Toa do duoc nhap vao
//Nhap toa do
while(1)
{
printf("Toa do cua x la: ");
scanf("%d",&y);
printf("Toa do cua y la: ");
scanf("%d",&x);
if(checkCoordinate(x,y)) //Neu x,y thuoc mang thi thoat ra khoi loop
    break;
else
    printf("Diem khong nam trong ma tran\n"); //Neu x,y khong thuoc mang thi lap lai loop
}
findShortestPath(x,y);
}

//Ham kiem tra toa do x,y co nam trong mang
bool checkCoordinate(int x, int y) {
    bool ret = false;
    if (x < MAX_ROW  &&y < MAX_COLUMN && 0<=x && 0<=y) //Neu 0<=x<9 va 0<=y<9 thi x,y co nam trong mang
        {
            ret = true;
        }
    return ret;
}

//Tim nhung diem quanh diem x,y co gia tri bang 1 va luu toa do nhung diem do vao mang surroundingPnt
int findSurroundingPoint(int x, int y, point_t surroundingPnt[]){
 int tempCnt = 0;
                //Kiem tra diem nam ben phai x,y nam trong mang va diem do co gia tri =1
                if ((checkCoordinate(x, y+1) == true) && (matrix[x][ y+1].value == 1)){
                            surroundingPnt[tempCnt ] = matrix[x][y+1];
                            tempCnt++;
                }
                //Kiem tra diem nam ben duoi x,y nam trong mang va diem do co gia tri =1
                if ((checkCoordinate(x+1, y) == true) && (matrix[x+1][y].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[x+1][y];
                            tempCnt++;
                }
                //Kiem tra diem nam ben trai x,y nam trong mang va diem do co gia tri =1
                if ((checkCoordinate(x, y-1) == true) && (matrix[x][y-1].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[x][y-1];
                            tempCnt++;
                }
                //Kiem tra diem nam ben tren x,y nam trong mang va diem do co gia tri =1
                if ((checkCoordinate(x-1, y) == true) && (matrix[x-1][y].value == 1)) {
                            surroundingPnt[tempCnt ] = matrix[x-1][ y];
                            tempCnt++;
                }
            return tempCnt; //So diem co the den duoc
}

void findShortestPath (int x, int y)
{
        int count;
        int row_temp,col_temp;
        point_t temp;
        point_t pp[4];
        Queue queue;
        Queue *q=&queue;
        initQueue(q); // Khoi tao hang
        matrix[0][0].visited=true; //Danh dau O(0,0) la da qua
        enQueue(q,matrix[0][0]); //Cho diem dau tien O(0,0) vao hang
        bool found=false;
        //Tim diem can tim va luu lai nhung diem ca di qua vao con cho cua diem tiep theo
        while (isEmpty(queue) == false&&found==false) //Neu khong con phat tu nao trong hang hoac tim thay diem can tim => thoat ra khoi loop
        {
            temp=deQueue(q); //lay phan tu dau cua hang luu vao bien temp
            count=findSurroundingPoint(temp.row,temp.column,pp);
            for(int i=0;i<count;i++)
                {
                if(matrix[pp[i].row][pp[i].column].visited==false)
                    {
                        matrix[pp[i].row][pp[i].column].visited=true; //chuyen thanh da qua
                        matrix[pp[i].row][pp[i].column].prev = &matrix[temp.row][temp.column]; //Luu dia chi cua diem truoc do vao
                        if(pp[i].row==x&&pp[i].column==y) //Neu diem co cung toa do voi diem can tim thi thoat ra khoi vong lap
                        {
                            found=true;
                            break;
                        }
                        else
                        {
                            enQueue(q,matrix[pp[i].row][pp[i].column]); //Cho diem do vao hang
                        }
                    }
                }
        }
        //Vong lap tim ra duong di nhanh nhat vi cac duong di deu bat dau o mot diem va duoc tang len lan luot
        if(found==true) //Neu tim duoc diem
        {
            printf("\nCo duong tu O(0,0) den A(%d,%d)",y,x);
            printf("\n(%d,%d)",matrix[x][y].prev->column,matrix[x][y].prev->row );
            row_temp=matrix[x][y].prev->row;
            col_temp=matrix[x][y].prev->column;
            //Luu toa do tiep theo cua x va y vao bien row_temp col_temp
            for(int i=0;row_temp!=0||col_temp!=0;) //Vong lap se dung lai khi den diem O
            {
                printf("\n(%d,%d)",matrix[row_temp][col_temp].prev->column,matrix[row_temp][col_temp].prev->row );
                i=row_temp;
                row_temp=matrix[row_temp][col_temp].prev->row;
                if(row_temp==0&&col_temp==0)
                {
                    break;
                }
                col_temp=matrix[i][col_temp].prev->column;
                //luu lai 2 bien moi duoc lay tu 2 bien cu
            }
        }
        else
        {
            printf("Khong co duong tu O(0,0) den A(%d,%d)",y,x);
        }
}




