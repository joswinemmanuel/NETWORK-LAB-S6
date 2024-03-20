#include<stdio.h>
int main(){
    int incoming, outgoing, buck_size, n, store = 0;
    printf("Enter bucket size, outgoing rate and no of inputs : ");
    scanf("%d %d %d", &buck_size, &outgoing, &n);

    while (n != 0) {
        printf("Enter the incoming packet size : ");
        scanf("%d", &incoming);
        printf("Incoming packet size %d\n", incoming);
        if (incoming <= (buck_size - store)){
            store += incoming;
            printf("Bucket buffer size :  %d out of %d\n", store, buck_size);
        } else {
            printf("Dropped %d no of packets\n", incoming - (buck_size - store));
           
            store = buck_size;
            printf("Bucket buffer size :  %d out of %d\n", store, buck_size);
        }
       
        if(store>=outgoing){
        store=outgoing-store;
        }
       
        if(store<0){
        store=store*(-1);
        }
        printf("After outgoing ,  There are %d  out of %d packets left in buffer\n", store, buck_size);
        n--;
    }
}

/*
Enter bucket size, outgoing rate and no of inputs : 1000 100 5
Enter the incoming packet size : 100
Incoming packet size 100
Bucket buffer size :  100 out of 1000
After outgoing ,  There are 0  out of 1000 packets left in buffer
Enter the incoming packet size : 200
Incoming packet size 200
Bucket buffer size :  200 out of 1000
After outgoing ,  There are 100  out of 1000 packets left in buffer
Enter the incoming packet size : 200
Incoming packet size 200
Bucket buffer size :  300 out of 1000
After outgoing ,  There are 200  out of 1000 packets left in buffer
Enter the incoming packet size : 300
Incoming packet size 300
Bucket buffer size :  500 out of 1000
After outgoing ,  There are 400  out of 1000 packets left in buffer
Enter the incoming packet size : 100
Incoming packet size 100
Bucket buffer size :  500 out of 1000
After outgoing ,  There are 400  out of 1000 packets left in buffer
*/
