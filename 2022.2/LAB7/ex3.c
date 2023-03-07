int main(void){
    int i,temp;
    int val[] = {1,2,3,4,5,6,7,8,9,10};
    for(i=0;i<10;i++){
        temp = val[i]*val[i];
        printf("%d\n",temp);
    }
    return 0;
}