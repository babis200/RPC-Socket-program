#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netdb.h>

#include <unistd.h>

void error(char * msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char * argv[]) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    if (argc < 3) {		//πρότυπο χρήσης
        printf("usage %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);	//πόρτα
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //άνοιγμα socket IPv4, TCP 

    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);		//λάβε host
    if (server == NULL) {
        printf("ERROR, no such host\n");
        exit(0);
    }
	
	//προετοιμασία socket
    bzero((char * ) & serv_addr, sizeof(serv_addr));	
    serv_addr.sin_family = AF_INET;
    bcopy((char * ) server -> h_addr, (char * ) & serv_addr.sin_addr.s_addr, server -> h_length);
    serv_addr.sin_port = htons(portno);

    printf("Trying to connect...\n");

    if (connect(sockfd, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Connected.\n");

	int flag=1;			//όταν flag == 0 κλείνει το πρόγραμμα
	int choice;
	int i;
	int n;
	float r;
	int *X, *Y;
	
	float metre;		//απάντηση στο 1
	int inner_prod;		//απάντηση στο 2
	float avg[2];		//avg[0] == X_avg, ang[1] == Y_avg
	float *res4;		//apanthsh sto 4
    do {

        printf("==========================\n");
        printf("=====ASK1 Operations=====\n");
        printf("Baltatzidis Charalampos AM:18390214\n");
        printf("==========================\n");
        printf("1. metre of X[]\n");
        printf("2. inner product of X[] and Y[]\n");
        printf("3. average of X[] and Y[]\n");
        printf("4. r*(X[]+Y[])\n");
        printf("5. Quit\n");
        printf("==========================\n");
        printf("Choice: ");
        scanf("%d", & choice);
        printf("==========================\n");

        send(sockfd, & choice, sizeof(int), 0);

        if (choice == 1) {

            //metre of X[]

            printf("Give size of X[]: ");
            scanf("%d", & n);
			
			send(sockfd, &n, sizeof(int), 0);	//στειλε το μέγεθος του Χ
            
			X=(int *)malloc(n*sizeof(int));
			
            printf("\n");

            for (i = 0; i < n; i++) {
                printf("X[%d] = ", i);		//διάβασε τις τιμές του Χ
                scanf("%d", &X[i]);
            }
	
            send(sockfd,X,n*sizeof(int),0);		//στειλε το Χ
			
			recv(sockfd,&metre,sizeof(float),0);	//λάβε την απάντηση
           
			printf("\n");
			printf("Metre of X[] == %.2f\n", metre);
			printf("\n");
            

        } else if (choice == 2) {

            //inner product of X[] and Y[]

            printf("Give size of X[] and  Y[]: ");
            scanf("%d", & n);
            n *= 2;
            
            X=(int *)malloc(n*sizeof(int));
			
			send(sockfd, &n, sizeof(int), 0);		//στειλε το μέγεθος των Χ και Υ επι 2
			
            printf("\n");

            for (i = 0; i < n / 2; i++) {
                printf("X[%d] = ", i);			//διάβασε τις τιμές του Χ
                scanf("%d", &X[i]);
            }
            int j = 0;
            for (i; i < n; i++) {
                printf("Y[%d] = ", j);			//διάβασε τις τιμές του Υ
                scanf("%d", & X[i]);
                j++;
            }

            send(sockfd,X,n*sizeof(int),0);		//στειλε το Χ και το Υ σε ένα πινακα
			
			recv(sockfd,&inner_prod,sizeof(int),0);		//λάβε την απάντηση

            
			printf("\n");
			printf("Inner product of X[] and Y[] : %d\n", inner_prod);
            printf("\n");
            

        } else if (choice == 3) {

            //average of X[] and Y[]

            printf("Give size of X[] and  Y[]: ");	
            scanf("%d", & n);

            X=(int *)malloc(n*sizeof(int));
			Y=(int *)malloc(n*sizeof(int));
			
			send(sockfd, &n, sizeof(int), 0);	//στειλε το μέγεθος των Χ και Υ

            printf("\n");

            for (i = 0; i < n; i++) {
                printf("X[%d] = ", i);	//διάβασε τις τιμές του Χ
                scanf("%d", & X[i]);
            }

            for (i = 0; i < n; i++) {
                printf("Y[%d] = ", i);	//διάβασε τις τιμές του Υ
                scanf("%d", & Y[i]);
            }

            send(sockfd,X,n*sizeof(int),0);	//στειλε το Χ
            send(sockfd,Y,n*sizeof(int),0);	//στειλε το Υ

			recv(sockfd,&avg[0],sizeof(float),0); 	//λάβε μέση τιμή του Χ
			recv(sockfd,&avg[1],sizeof(float),0);	//λάβε μέση τιμή του Υ

           
            printf("\n");
			printf("Average of X[] == %.2f\n", avg[0]);
			printf("Average of Y[] == %.2f\n", avg[1]);
			printf("\n");
            

        } else if (choice == 4) {
            //r*(X[]+Y[])

            printf("Give size of X[] and  Y[]: ");
            scanf("%d", & n);

            send(sockfd, &n, sizeof(int), 0);	//στειλε το μέγεθος των Χ και Υ
			
			X=(int *)malloc(n*sizeof(int));
            
			
			printf("\n");

            for (i = 0; i < n; i++) {
                printf("X[%d] = ", i);		//διάβασε τις τιμές του Χ
                scanf("%d", & X[i]);
            }

            int dummy;
            for (i = 0; i < n; i++) {
                printf("Y[%d] = ", i);
                scanf("%d", & dummy);		//διάβασε τις τιμές του Υ
                X[i] += dummy; 				//add x[i] and y[i] in X[i]
            }
			
			send(sockfd,X,n*sizeof(int),0); 	//στείλε Χ+Υ
			
            printf("Give floating number r: ");		//λάβε ρ
            scanf("%f", &r);

            send(sockfd, &r, sizeof(float), 0);		// στέλε ρ

            printf("\n");
			
			res4=(float *)malloc(n*sizeof(float));	
            recv(sockfd,res4,n*sizeof(float),0);	//λάβε απάντηση

            
			printf("\n");
			for (i = 0; i < n; i++)
				printf("%.2f*(X[%d]+Y[%d]) == %.2f\n", r, i, i, res4[i]);
			printf("\n");
            
        } else if (choice == 5) {		//κλείσιμο
            flag = 0;
        } else {
            printf("Invalid Choice. Try Again.\n\n");
        }
    } while (flag);

    close(sockfd);

    return 0;
}