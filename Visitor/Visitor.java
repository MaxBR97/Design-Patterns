
interface Visitor {
    Text visit(Text c, int times);
    Number visit(Number n, int times);
    ComplexNumber visit(ComplexNumber c,int times);
}