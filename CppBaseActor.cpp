// Sets default values
ACppBaseActor::ACppBaseActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACppBaseACtor::BeginPlay()
{
	Super::BeginPlay();
	ShowActorInformation();
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTIme)
{
	Sper::Tick(DeltaTime);
}

void ACppBaseActor::ShowActorInformation()
{
	UE_LOG(LogTemp, Display, TEXT("Instance name: %s"), PlayerName);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, PlayerName, true, FVector2D(2.0f, 2.0f));
	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("IsAlive: %i"), IsALive);
}