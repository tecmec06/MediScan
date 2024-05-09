#include <stdio.h>
#include <math.h>
#include <string.h>
int begin();
int patient();
int stock();
int expenseincome();
int staffmanagement();
int main()
{
    int n;
    n = begin();
    if (n == 1)
    {
        patient();
    }
    else if (n == 2)
    {
        staffmanagement();
    }
    else if (n == 3)
    {
        stock();
    }
    else if (n == 4)
    {
        expenseincome();
    }
    return 0;
}
int begin()
{
    int n;
    char data[50];
    FILE *start;
    start = fopen("start.txt", "r");
    while (!feof(start))
    {
        fgets(data, 50, start);
        printf("%s", data);
    }
    printf("\n");
    scanf("%d", &n);
    fclose(start);
    return n;
}
void new (int d, int m, int y);
void old(int d, int m, int y);
void disease(int d, int m, int y);
void doctor(int i, int d, int m, int y);
void medicine();
void test(int i);
int patient()
{
    int n, d, m, y;
    printf("Please Enter Todays Date(dd/mm/yyyy) - ");
    scanf("%d/%d/%d", &d, &m, &y);
    printf("Please select by corresponding number: \n1)New Patient \n2)Old Patient\n");
    scanf("%d", &n);
    if (n == 1)
    {
        new (d, m, y);
    }
    else
    {
        old(d, m, y);
    }
    return 0;
}
void old(int d, int m, int y)
{
    int result = 1, d1, m1, y1, bill;
    char temp4[2];
    char temp[70];
    char temp2[8];
    char temp3[8] = "START";
    FILE *oldpat, *list;
    oldpat = fopen("patientinfo.txt", "r");
    list = fopen("patientlist.txt", "r");
    while (!feof(list))
    {
        fgets(temp, 4, list);
        printf("%s", temp);
    }
    printf("\n");
    fclose(list);
    fseek(oldpat, 0, SEEK_SET);
    fflush(stdin);
    gets(temp4);
    strcat(temp3, temp4);
    while (result != 0)
    {
        fgets(temp2, 8, oldpat);
        if (strcmp(temp2, temp3) == 0)
        {
            while (result != 0)
            {
                fgets(temp, 70, oldpat);
                if (strlen(temp) == 4)
                {
                    break;
                }
                printf("%s", temp);
            }
            fscanf(oldpat, "\n%d/%d/%d", &d1, &m1, &y1);
            fscanf(oldpat, "\n%d", &bill);
            break;
        }
        else
        {
            continue;
        }
    }
    if (y - y1 == 0)
    {
        if (m - m1 == 0)
        {
            printf("Next appointment date - %d/%d/%d\n", d1, m1 + 1, y1);
        }
        else if (m - m1 == 1)
        {
            if (d - d1 < 0)
            {
                printf("Next appointment date - %d/%d/%d\n", d1, m1 + 1, y1);
            }
            else if (d - d1 >= 0)
            {
                printf("Next appointment date - %d/%d/%d\n", d, m1 + 1, y1);
            }
        }
        else if (m - m1 >= 2)
        {
            printf("Next appointment date - %d/%d/%d\n", d, m, y);
        }
    }
    else if (y - y1 > 0)
    {
        if (m1 == 12 && m == 1)
        {
            if (d - d1 < 0)
            {
                printf("Next appointment date - %d/%d/%d\n", d1, m, y);
            }
            else if (d - d1 >= 0)
            {
                printf("Next appointment date - %d/%d/%d\n", d, m, y);
            }
        }
        else
        {
            printf("Next appointment date - %d/%d/%d\n", d, m, y);
        }
    }
    fclose(oldpat);
    medicine(bill);
}
void new (int d, int m, int y)
{
    int n = 0, k;
    char temp1[60];
    FILE *newpat = fopen("patientinfo.txt", "a");
    FILE *list = fopen("patientlist.txt", "a+");
    fseek(list, 0, SEEK_SET);
    while (!feof(list))
    {
        fgets(temp1, 60, list);
        n++;
    }
    if (n <= 9)
    {
        k = 0;
    }
    else
    {
        k = floor(n / 10);
        n = n % 10;
    }
    fprintf(list, "\n%d%d) ", k, n);
    printf("Please enter the following details: \nName - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nSTART%d%d\nName - %s", k, n, temp1);
    fprintf(list, "%s", temp1);
    printf("Age - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nAge - %s", temp1);
    printf("Sex - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nSex - %s", temp1);
    printf("Address - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nAddress - %s", temp1);
    printf("Contact Number - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nContact Number - %s", temp1);
    printf("Email - ");
    fflush(stdin);
    gets(temp1);
    fprintf(newpat, "\nEmail - %s", temp1);
    fclose(newpat);
    fclose(list);
    disease(d, m, y);
}
void disease(int d, int m, int y)
{
    int n, i, result = 1;
    char temp[70];
    char temp1[5];
    FILE *disease = fopen("disease.txt", "r");
    while (result != 0)
    {
        fgets(temp, 70, disease);
        if (strlen(temp) == 4)
        {
            break;
            result = 0;
        }
        printf("%s", temp);
    }
    scanf("%d", &n);
    fseek(disease, 0, SEEK_SET);
    fgets(temp, 70, disease);
    for (i = 0; i < n; i++)
    {
        fgets(temp1, 5, disease);
        fgets(temp, 70, disease);
    }
    FILE *newpat = fopen("patientinfo.txt", "a");
    fprintf(newpat, "\nDisease/emergency - %s", temp);
    fclose(newpat);
    fclose(disease);
    doctor(i, d, m, y);
}
void doctor(int i, int d, int m, int y)
{
    int bill = 0;
    int n, result = 1;
    char temp[70];
    char temp1[3];
    FILE *list = fopen("doctorlist.txt", "r");
    FILE *newpat = fopen("patientinfo.txt", "a");
    if (i <= 5)
    {
        n = 1;
        fgets(temp1, 3, list);
        fgets(temp, 70, list);
        fprintf(newpat, "Doctor assigned -%sLast Appointment Date  - %d/%d/%d\nEND\n%d/%d/%d", temp, d, m, y, d, m, y);
        printf("Doctor Assigned -%s", temp);
    }
    else
    {
        n = i - 4;
        for (int j = 0; j < n; j++)
        {
            fgets(temp1, 3, list);
            fgets(temp, 70, list);
        }
        fprintf(newpat, "Doctor assigned -%sLast Appointment Date  - %d/%d/%d\nEND\n%d/%d/%d", temp, d, m, y, d, m, y);
        printf("Doctor Assigned -%s", temp);
    }
    while (result != 0)
    {
        fgets(temp, 70, list);
        if (strlen(temp) == 4)
        {
            break;
        }
    }
    for (int j = 0; j < (n - 1); j++)
    {
        fgets(temp, 70, list);
    }
    fscanf(list, "\n%d", &bill);
    fclose(list);
    fprintf(newpat, "\n%d", bill);
    fclose(newpat);
    medicine(bill);
}
void medicine(int z)
{
    int result = 1;
    int m;
    printf("Enter total number of medicines prescribed: ");
    scanf("%d", &m);
    FILE *prescription = fopen("medicine.txt", "r");
    int input2, input3, input4;
    char input[2];
    char temp[60];
    char temp3[8];
    for (int k = 0; k < m; k++)
    {
        char temp2[8] = "START";
        fseek(prescription, 0, SEEK_SET);
        while (result != 0)
        {
            fgets(temp, 60, prescription);
            if (strlen(temp) == 4)
            {
                break;
            }
            printf("%s", temp);
        }
        fflush(stdin);
        gets(input);
        strcat(temp2, input);
        while (result != 0)
        {
            fgets(temp3, 8, prescription);
            if (strcmp(temp3, temp2) == 0)
            {
                while (result != 0)
                {
                    fgets(temp, 60, prescription);
                    if (strlen(temp) == 4)
                    {
                        break;
                    }
                    printf("%s", temp);
                }
                scanf("%d", &input2);
                for (int j = 0; j < (input2 - 1); j++)
                {
                    fgets(temp, 60, prescription);
                }
                printf("Enter quantity: ");
                scanf("%d", &input3);
                fscanf(prescription, "\n%d", &input4);
                z = z + (input3 * input4);
                fseek(prescription, 0, SEEK_SET);
                break;
            }
        }
    }
    test(z);
    fclose(prescription);
}
void test(int i)
{
    int m, n, input, result = 1;
    char temp[60];
    FILE *test = fopen("test.txt", "r");
    printf("Enter Number of tests Prescribed: ");
    scanf("%d", &m);
    for (int j = 0; j < m; j++)
    {
        fseek(test, 0, SEEK_SET);
        while (result != 0)
        {
            fgets(temp, 60, test);
            if (strlen(temp) == 4)
            {
                break;
            }
            printf("%s", temp);
        }
        scanf("%d", &n);
        for (int k = 0; k < (n - 1); k++)
        {
            fgets(temp, 60, test);
        }
        fscanf(test, "\n%d", &input);
        i = i + input;
    }
    printf("Bill = Rs.%d", i);
}
void doctorstaff();
void otherstaff();
int staffmanagement()
{
    int n;
    printf("Please select by corresponding number: \n1)Doctor staff \n2)Other staff\n");
    scanf("%d", &n);
    if (n == 1)
    {
        doctorstaff();
    }
    else
    {
        otherstaff();
    }
    return 0;
}
void doctorstaff()
{
    char n[1];
    char temp1[7] = "START";
    char temp[70];
    char temp2[7];
    char temp3;
    int start = 1;
    printf("Please select by corresponding class: \n1)Physician \n2)Orthopediatrics \n3)Dentist \n4)Dermatologist \n5)Cardiologist \n6)Surgeon\n");
    fflush(stdin);
    gets(n);
    strcat(temp1, n);
    FILE *doc;
    doc = fopen("doctorsstaff.txt", "r");
    while (start != 0)
    {
        fgets(temp2, 7, doc);
        if (strcmp(temp2, temp1) == 0)
        {
            while (start != 0)
            {
                fgets(temp, 70, doc);
                if (strlen(temp) == 4)
                {
                    break;
                }
                printf("%s", temp);
            }
            break;
        }
        else
        {
            continue;
        }
    }
    fclose(doc);
}
void otherstaff()
{
    int result = 1;
    char temp[70];
    char temp1[7] = "START";
    char temp2[8] = "START";
    char temp3[9] = "START";
    char temp11[7];
    char temp12[8];
    char temp13[9];
    char input1[1];
    char input2[1];
    char input3[1];
    printf("Please select class by corresponding number : \n1) First class\n2) Second class\n3) Third class\n4) Fourth class\n");
    fflush(stdin);
    gets(input1);
    strcat(temp1, input1);
    strcat(temp2, input1);
    strcat(temp3, input1);
    FILE *box;
    box = fopen("otherstaff.txt", "r");
    while (result != 0)
    {
        fgets(temp11, 7, box);
        if (strcmp(temp11, temp1) == 0)
        {
            while (result != 0)
            {
                fgets(temp, 70, box);
                if (strlen(temp) == 4)
                {
                    break;
                }
                printf("%s", temp);
            }
            fflush(stdin);
            gets(input2);
            strcat(temp2, input2);
            strcat(temp3, input2);
            while (result != 0)
            {
                fgets(temp12, 8, box);
                if (strcmp(temp12, temp2) == 0)
                {
                    while (result != 0)
                    {
                        fgets(temp, 70, box);
                        if (strlen(temp) == 4)
                        {
                            break;
                        }
                        printf("%s", temp);
                    }
                    fflush(stdin);
                    gets(input3);
                    strcat(temp3, input3);
                    while (result != 0)
                    {
                        fgets(temp13, 9, box);
                        if (strcmp(temp13, temp3) == 0)
                        {
                            while (result != 0)
                            {
                                fgets(temp, 70, box);
                                if (strlen(temp) == 4)
                                {
                                    break;
                                }
                                printf("%s", temp);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    fclose(box);
}
int stock()
{
    int z;
    printf("Select By corresponding number:\n1. Medicine\n2. Test\n3. Equipments\n");
    scanf("%d", &z);
    if (z == 2)
    {
        char *filename = "testcost.txt";
        FILE *fp = fopen(filename, "r");
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            putchar(ch);
        }
        fclose(fp);
    }
    if (z == 3)
    {
        char *filename = "equipmentscost.txt";
        FILE *fp = fopen(filename, "r");
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            putchar(ch);
        }
        fclose(fp);
    }
    if (z == 1)
    {
        int result = 1;
        char input[2];
        char temp2[8];
        char temp1[8] = "START";
        char temp[70];
        char *filename = "medicinecost.txt";
        FILE *fp = fopen(filename, "r");
        while (result != 0)
        {
            fgets(temp, 70, fp);
            if (strlen(temp) == 4)
            {
                break;
            }
            printf("%s", temp);
        }
        fflush(stdin);
        gets(input);
        strcat(temp1, input);
        printf("   Medicine                      |Cost Price|Sell Price| Stock ");
        while (result != 0)
        {
            fgets(temp2, 8, fp);
            if (strcmp(temp2, temp1) == 0)
            {
                while (result != 0)
                {
                    fgets(temp, 70, fp);
                    if (strlen(temp) == 4)
                    {
                        break;
                    }
                    printf("%s", temp);
                }
                break;
            }
        }
        fclose(fp);
    }
    return 0;
}
int expenses();
int income();
int expenseincome()
{
    int n;
    printf("Please select by corresponding number: \n 1) Expenses Management\n 2) Income Management\n");
    scanf("%d", &n);
    if (n == 1)
    {
        expenses();
    }
    else if (n == 2)
    {
        income();
    }
    return 0;
}
void salaries();
void taxes();
void bills();
void equipment();
void medicalorder();
int expenses()
{
    int n;
    printf("Please select by corresponding number: \n1) Salaries \n2) Taxes \n3) Bills \n4) Equipment \n5) Medicine Order \n");
    scanf("%d", &n);
    if (n == 1)
    {
        salaries();
    }
    else if (n == 2)
    {
        taxes();
    }
    else if (n == 3)
    {
        bills();
    }
    else if (n == 4)
    {
        equipment();
    }
    else if (n == 5)
    {
        medicalorder();
    }
    return 0;
}
void salaries()
{
    int n, result = 1, tsalary = 0, salary;
    char data[50];
    FILE *salary1;
    salary1 = fopen("salary.txt", "r");
    while (result != 0)
    {
        fgets(data, 50, salary1);
        if (strlen(data) == 4)
        {
            break;
        }
        printf("%s", data);
    }
    for (int i = 0; i <= 13; i++)
    {
        fscanf(salary1, "\n%d", &salary);
        tsalary = tsalary + salary;
    }
    printf("\nTotal expenditure on salary = %d INR.\n", tsalary);
    fclose(salary1);
}
void taxes()
{
    float t;
    printf("Enter the total revenue earned by the hospital in INR : ");
    scanf("%f", &t);
    printf("As per Government rules the applied taxes will be 12 percent. \nThe taxes paid by the hospital = %.2f INR.\n", ((12 * t) / 100));
}
void bills()
{
    float e, w;
    printf("Enter the power used by hospital in kWh : ");
    scanf("%f", &e);
    printf("Enter the water used by hospital in L : ");
    scanf("%f", &w);
    printf("\nThe Electricity bill paid by the hospital = %.2f INR.\n", e * 5.43);
    printf("The Water bill paid by the hospital = %.2f INR.\n", w * 1);
}
void equipment()
{
    float sy, g, c, sg, f, sc, st, nh, v, m, scp, a, stp, bp, o, s;
    printf("Enter the number of syringe bought by hospital : ");
    scanf("%f", &sy);
    printf("Enter the number of gauze bought by hospital : ");
    scanf("%f", &g);
    printf("Enter the number of cotton bought by hospital : ");
    scanf("%f", &c);
    printf("Enter the number of surgical gloves bought by hospital : ");
    scanf("%f", &sg);
    printf("Enter the number of forceps bought by hospital : ");
    scanf("%f", &f);
    printf("Enter the number of scissors bought by hospital : ");
    scanf("%f", &sc);
    printf("Enter the number of stitches bought by hospital : ");
    scanf("%f", &st);
    printf("Enter the number of needle holder bought by hospital : ");
    scanf("%f", &nh);
    printf("Enter the number of ventilators bought by hospital : ");
    scanf("%f", &v);
    printf("Enter the number of masks bought by hospital : ");
    scanf("%f", &m);
    printf("Enter the number of surgical caps bought by hospital : ");
    scanf("%f", &scp);
    printf("Enter the number of apron bought by hospital : ");
    scanf("%f", &a);
    printf("Enter the number of stethoscope bought by hospital : ");
    scanf("%f", &stp);
    printf("Enter the number of BP Apparatus bought by hospital : ");
    scanf("%f", &bp);
    printf("Enter the number of oxygen cylinders bought by hospital : ");
    scanf("%f", &o);
    printf("Enter the number of stretchers bought by hospital : ");
    scanf("%f", &s);
    printf("\nThe amount paid by the hospital for syringe = %.2f INR.\n", sy * 3);
    printf("The amount paid by the hospital for gauze = %.2f INR.\n", g * 4);
    printf("The amount paid by the hospital for cotton = %.2f INR.\n", c * 80);
    printf("The amount paid by the hospital for surgical gloves = %.2f INR.\n", sg * 15);
    printf("The amount paid by the hospital for forceps = %.2f INR.\n", f * 350);
    printf("The amount paid by the hospital for scissors = %.2f INR.\n", sc * 220);
    printf("The amount paid by the hospital for stitches = %.2f INR.\n", st * 350);
    printf("The amount paid by the hospital for needle holder = %.2f INR.\n", nh * 475);
    printf("The amount paid by the hospital for ventilators = %.2f INR.\n", v * 350000);
    printf("The amount paid by the hospital for masks = %.2f INR.\n", m * 3);
    printf("The amount paid by the hospital for surgical caps = %.2f INR.\n", scp * 5);
    printf("The amount paid by the hospital for apron = %.2f INR.\n", a * 1200);
    printf("The amount paid by the hospital for stethoscope = %.2f INR.\n", stp * 800);
    printf("The amount paid by the hospital for BP Apparatus = %.2f INR.\n", bp * 2500);
    printf("The amount paid by the hospital for oxygen cylinders = %.2f INR.\n", o * 6500);
    printf("The amount paid by the hospital for stretchers = %.2f INR.\n", s * 15000);
    printf("\nThe total expenditure paid by the hospital for medical equipment = %.2f INR.\n", (sy * 3 + g * 4 + c * 80 + sg * 15 + f * 350 + sc * 220 + st * 350 + nh * 475 + v * 350000 + m * 3 + scp * 5 + a * 1200 + stp * 800 + bp * 2500 + o * 6500));
}
void medicalorder()
{
    int n = 1, input2, input3, input4;
    char temp1[8] = "START";
    char temp2[8];
    char input[2];
    char data[70];
    FILE *start;
    start = fopen("medicineorder.txt", "r");
    while (n != 0)
    {
        fgets(data, 70, start);
        if (strlen(data) == 4)
        {
            break;
        }
        printf("%s", data);
    }
    fflush(stdin);
    gets(input);
    strcat(temp1, input);
    printf("Select medicine to be ordered by corresponding number: ");
    while (n != 0)
    {
        fgets(temp2, 8, start);
        if (strcmp(temp2, temp1) == 0)
        {
            while (n != 0)
            {
                fgets(data, 70, start);
                if (strlen(data) == 4)
                {
                    break;
                }
                printf("%s", data);
            }
            scanf("%d", &input2);
            for (int j = 0; j < (input2 - 1); j++)
            {
                fgets(data, 70, start);
            }
            printf("Enter amount to be ordered: ");
            scanf("%d", &input4);
            fscanf(start, "\n%d", &input3);
            break;
        }
    }
    printf("The amount to be paid for the medicine = %d INR.", input3 * input4);
}
void appointmentfee();
void medicineprofit();
void testprofit();
int income()
{
    int n;
    printf("Please select by corresponding number: \n1) Appointment Fee \n2) Medicine Profit \n3) Test Profit \n");
    scanf("%d", &n);
    if (n == 1)
    {
        appointmentfee();
    }
    else if (n == 2)
    {
        medicineprofit();
    }
    else if (n == 3)
    {
        testprofit();
    }
    return 0;
}
void appointmentfee()
{
    int n = 1, m, total = 0;
    char data[50];
    FILE *start;
    start = fopen("appointmentfee.txt", "r");
    while (n != 0)
    {
        fgets(data, 50, start);
        if (strlen(data) == 4)
        {
            break;
        }
        printf("%s", data);
    }
    while (n != 0)
    {
        fscanf(start, "\n%d", &m);
        total = total + m;
        if (m == 2000)
        {
            break;
        }
    }
    printf("\nIncome from appointment fee = %d INR.\n", total);
}
void medicineprofit()
{
    int n = 1, input2, input3, input4;
    char temp1[8] = "START";
    char temp2[8];
    char input[2];
    char data[70];
    FILE *start;
    start = fopen("medicineprofit.txt", "r");
    while (n != 0)
    {
        fgets(data, 70, start);
        if (strlen(data) == 4)
        {
            break;
        }
        printf("%s", data);
    }
    fflush(stdin);
    gets(input);
    strcat(temp1, input);
    printf("   Medicine                      |  Profit |");
    while (n != 0)
    {
        fgets(temp2, 8, start);
        if (strcmp(temp2, temp1) == 0)
        {
            while (n != 0)
            {
                fgets(data, 70, start);
                if (strlen(data) == 4)
                {
                    break;
                }
                printf("%s", data);
            }
            break;
        }
    }
    fclose(start);
}
void testprofit()
{
    int n;
    char data[50];
    FILE *start;
    start = fopen("testprofit.txt", "r");
    while (!feof(start))
    {
        fgets(data, 50, start);
        printf("%s", data);
    }
    fclose(start);
}