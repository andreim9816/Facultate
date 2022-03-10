
void afis1()
{   char c;
    scanf("%c",&c);
    if(c>='a' && c<='z')
        printf("%c",c);
    else printf("%c",c+32);
}

void afis2(int a,char op, int b)
{

    switch(op)
    {
        case '+': printf("%d",a+b); break;
        case '-': printf("%d",a-b); break;
        case '*': printf("%d",a*b); break;
        case '/':
                    if(b==0)
                    printf("Nu e bine");
                    else printf("%d",a/b);
                    break;
        case '%':   if(b==0) printf("NU e bine");
                    else printf("%d",a%b);
                    break;

    }

}
