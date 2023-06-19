#include "server.h"
#include "ui.h"
socketServer::socketServer(int port): serverPort(port){
    int flag =1,len = sizeof(int);
    this->masterSock = socket(PF_INET, SOCK_STREAM, 0); //?

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(port);
#if 0
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
#else
    this->serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//INADDR_ANY;
#endif
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    if(setsockopt(this->masterSock,SOL_SOCKET,SO_REUSEADDR,&flag,len)==-1){
        perror("setsockopt");
        exit(1);
    }

    bind(this->masterSock, (struct sockaddr *) &this->serverAddr, sizeof(this->serverAddr)); //set server socket

    if(!listen(this->masterSock,MAX_USER))
        printf("Server is listening on %d\n",port);
    else
        perror("listen");

    FD_ZERO(&this->afds);
    FD_SET(this->masterSock,&this->afds);
    FD_SET(0,&this->afds);

    this->nfds = sizeof(this->afds);

    // new shm_fd

    SHARED_MEMORY_SIZE  = sizeof(LMS);

    this->lmsFd = shm_open("/lmsMem",O_CREAT | O_RDWR,0666);
    if(this->lmsFd < 0){
        std::cerr << "Error creating shared memory object." << std::endl;
    }
    if (ftruncate(this->lmsFd, SHARED_MEMORY_SIZE) == -1) {
        std::cerr << "Error setting the size of shared memory." << std::endl;
    }
    sharedMemory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, this->lmsFd, 0);
    if (sharedMemory == MAP_FAILED) {
        std::cerr << "Error mapping shared memory." << std::endl;
    }
    LMS* shared_data = static_cast<LMS*>(sharedMemory);
    shared_data->reset();

    strcpy(shared_data->username[0],"Dave");

    shared_data->userIdx = 1;
    std::cout << shared_data->username[0] << std::endl;

    LIBRARY_MEMORY_SIZE = sizeof(LIBRARY);

    this->libFd = shm_open("/libMem", O_CREAT | O_RDWR, 0666);
    if(this->libFd < 0){
        std::cerr << "Error creating shared memory object." << std::endl;
    }
    if (ftruncate(this->libFd, LIBRARY_MEMORY_SIZE) == -1) {
        std::cerr << "Error setting the size of shared memory." << std::endl;
    }
    libraryMemory = mmap(NULL, LIBRARY_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, this->libFd, 0);
    if (libraryMemory == MAP_FAILED) {
        std::cerr << "Error mapping shared memory." << std::endl;
    }
    LIBRARY* lib_data = static_cast<LIBRARY*>(libraryMemory);
    lib_data->init();

}

socketServer::~socketServer(){
    munmap(sharedMemory, SHARED_MEMORY_SIZE);
    close(this->lmsFd);
    std::cout << "Destructor !" << std::endl;
}
int socketServer::run(){
    while(1){
        memcpy(&this->rfds,&this->afds,sizeof(this->rfds));

        if(select(this->nfds,&this->rfds,(fd_set*)0,(fd_set*)0,(struct timeval *)0)<0)
            fprintf(stderr,"select is wrong\n");
        

        if(FD_ISSET(0,&this->rfds)){ //local machine input
            std::string cmd;
            std::getline(std::cin,cmd);// read(0,in,sizeof(in));
            if(cmd!="exit")
                continue;
            close(masterSock);
            return -1;
        }

        if(FD_ISSET(this->masterSock,&this->rfds)){ //the external connection to  
            this->createProcess();
        }
    }
    close(this->masterSock);
    return 0;
    
}
int socketServer::createProcess(){
    this->addrSize = sizeof(socklen_t);
    int ssock = accept(this->masterSock, (struct sockaddr *) &this->serverAddr, &this->addrSize);
    getpeername(ssock,(struct sockaddr*)&this->serverAddr,&this->addrSize);
    if(ssock<0){
        fprintf(stderr,"accept error !\n");
        return -1;
    }
    fprintf(stderr,"new client !\n");
    pid_t child = fork();
    if(!child){
        std::shared_ptr<UI> ui(new UI(ssock,this->sharedMemory,this->libraryMemory));
        ui->run();
        close(ssock);
        exit(0);
    }else{
        close(ssock);
    }

    return 1;

}
