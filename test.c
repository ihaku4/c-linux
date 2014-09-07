void main()
{
    int i = 0xfffffffff;
    printf("%d", 6/7);
    printf("%d", -6/7);
    printf("\n");
    printf("%X", 0xfff7&0x7f00);
    printf("\n%d, %x", -0xffffff, 0xffff);
    printf("\n%d, %x", i, i);
    printf("\n%d", sizeof(i));
    return;
}
