#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>

#include <stdint.h>
typedef unsigned __int16 WORD;

WORD bfType;

typedef struct {
    int bfSize;            //Размер файла в байтах	(Смещение 2, длина 4)
    int bfReserved1_2;            //Бесполезно (Смещение 8, длина 2)
    int bfOffBits;        //Смещение до самого изображения (Смещение 10, длина 4)
} bm_h;


typedef struct {
    int    biSize;         // размер струкуры в байтах:
    int    biWidth;        // ширина в точках
    int    biHeight;       // высота в точках
    WORD   biPlanes;       // всегда должно быть 1
    WORD   biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
    int    biCompression;

    int    biSizeImage;    // Количество байт в поле данных

    int    biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
    int    biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
    int    biClrUsed;      // Количество используемых цветов

    int    biClrImportant;
} BMP;


unsigned int get_width(unsigned int width) {
    while(width % 32 != 0) {
        width++;
    }
    return width;
}

unsigned int get_size(const unsigned char chars[4]) {
    unsigned int tmp = 0;
    tmp += chars[0];
    tmp += chars[1] << 8;
    tmp += chars[2] << 16;
    tmp += chars[3] << 24;
    return tmp;
}

FILE * get_input(char * input) {
    return fopen(input, "rb");
}

FILE * get_output(char * input) {
    return fopen(input, "wb");
}

unsigned int width;
unsigned int normal_width;
unsigned int height;

int bfOffBits;

char *input = "";
char *dir_file = "";
int write = 0;

void load_bmp_header(FILE *fin) {

    BMP bh;

    bm_h head;

    fread(&bfType, sizeof(char), 2, fin);
    fread(&head, sizeof(char), 12, fin);
    fread(&bh, sizeof(char), sizeof(BMP), fin );

    bfOffBits = head.bfOffBits;


    fseek(fin, head.bfOffBits, SEEK_SET);

    printf("load_bmp: good_1\n");

    height = bh.biHeight;
    width = bh.biWidth;
    normal_width = get_width(width);


    printf("%u %u %d %d\n", normal_width, height, sizeof(BMP), head.bfOffBits);
}

void load_bmp_map(FILE *fin, short pixel_map[height][width]) {
    unsigned char bytes[height][normal_width / 8];
    int c;
    int counter = -1;
    while((c = getc(fin)) != EOF) {
        counter++;
        if ((counter) / (normal_width / 8) < height) {
            bytes[(counter) / (normal_width / 8)][(counter) % (normal_width / 8)] = c;
        }

    }

    unsigned char bit;

    for (int i = height - 1; i >= 0; i--) {
        for (unsigned int j = 0; j < (normal_width / 8); j++) {
            bit = 0b10000000;
            for (int k = 1; k < 9; k++) {
                if (j * 8 + k > width) {
                    break;
                }
                // !(bit & bytes[i][j]) ? printf("%c", 'x') :printf("%c", ' ');
                pixel_map[height - 1 - i][j * 8 + k - 1] = (short) ((bit & bytes[i][j]) ? 1 : 0);
                bit = bit >> 1;
            }
        }
        //printf("\n");
    }

    //

    //
}

void write_pixel_map(short pixel_map[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel_map[i][j] == 1 ? printf("%c", 'x') :printf("%c", ' ');
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

short get_sum_neighbours(short pixel_map[height][width], int x, int y) {
    int sum = 0;
    int up, down, left, right;
    up = x + 1 == height ? 0 : x + 1;
    down = x - 1 == -1 ? ((int) height - 1) : x - 1;
    right = y + 1 == width ? 0 : y + 1;
    left = y - 1 == -1 ? (int) width - 1: y - 1;

    sum += pixel_map[up][left];
    sum += pixel_map[up][y];
    sum += pixel_map[up][right];
    sum += pixel_map[x][right];
    sum += pixel_map[down][right];
    sum += pixel_map[down][y];
    sum += pixel_map[down][left];
    sum += pixel_map[x][left];


    if (pixel_map[x][y] == 1) {
        if (sum == 2 || sum == 3) {
            return 1;
        }
        return 0;
    } else {
        if (sum == 3) {
            return 1;
        }
        return 0;
    }

}

void play_of_life(short pixel_map[height][width]) {
    short tmp_map[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tmp_map[i][j] = get_sum_neighbours(pixel_map, i, j);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel_map[i][j] = tmp_map[i][j];
        }
    }

}

char * utoa_builtin_div(uint32_t value, char *buffer)
{
    buffer += 11;

    *--buffer = 0;
    do
    {
        *--buffer = value % 10 + '0';
        value /= 10;
    }
    while (value != 0);
    return buffer;
}


void pixel_to_bytes(short pixel_map[height][width], unsigned char bytes[height][normal_width / 8]) {
    unsigned char bit;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < normal_width / 8; j++) {
            unsigned char c = 0b00000000;
            bit = 0b10000000;
            for (int k = 0; k < 8; k++) {
                if (j * 8 + k + 1 < width && pixel_map[i][j * 8 + k + 1] == 1) {
                    c += bit >> k;
                }
                bytes[height - 1 - i][j] = c;
            }
        }
    }
}

void write_in_file(short pixel_map[height][width], int num, FILE * fin, unsigned char out_file[bfOffBits]) {

    char tmp[11];
    char dir[1000] = "";
    strcpy(dir, dir_file);
    char file_name[1000] = "out_file";

    strcat(file_name, utoa_builtin_div(num, tmp));
    strncat(file_name, ".bmp",4);
    //printf("%s\n", file_name);
    strcat(dir, file_name);
    printf("%s\n", dir);


    FILE *fout = fopen(dir, "wb");

    //fwrite(&out_file, 1, bfOffBits, fout);
    for (int i = 0; i < bfOffBits; i++) {
        putc(out_file[i], fout);
    }



    unsigned char bytes[height][normal_width / 8];

    pixel_to_bytes(pixel_map, bytes);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < normal_width / 8; j++) {
            putc(bytes[i][j], fout);
        }
    }

    fclose(fout);

}

void get_out_file(unsigned char out_file[bfOffBits]) {
    FILE *fin = fopen(input, "rb");

    //fread(&out_file, 1, bfOffBits, fin);

    for (int i = 0; i < bfOffBits; i++) {
        out_file[i] = (char) getc(fin);
    }

    fclose(fin);
}

void program(FILE *fin, int max_inter, int dump_freq) {
    printf("program: good\n");
    load_bmp_header(fin);
    short pixel_map[height][width];

    unsigned char out_file[bfOffBits];
    get_out_file(out_file);

    load_bmp_map(fin, pixel_map);
    //play_of_life(pixel_map);

    write == 1 ? write_pixel_map(pixel_map) : 0;


    write_in_file(pixel_map, 0, fin, out_file);
    for (int i = 1; i < max_inter; i++) {
        for (int j = 0; j < dump_freq; j++) {
            play_of_life(pixel_map);
        }
        write_in_file(pixel_map, i * dump_freq, fin, out_file);
    }

}


int main(int argc, char *argv[]) {
    FILE *fin;
    FILE *fout;

/*
    input = "C:\\Users\\mailo\\CLionProjects\\play_in_life\\files\\download.bmp";
    "C:\\Users\\mailo\\CLionProjects\\play_in_life\\files\\premium.bmp"
    dir_file = "C:\\Users\\mailo\\CLionProjects\\play_in_life\\return\\";
    fin = get_input(input);
    program(fin, max_iter, dump_freq);
*/

    int do_program = 1;

    char string_console[1000];
    char input_file[1000];
    char output_dir[1000];

    int max_iter = 100;
    int dump_freq = 1;

    int in = 0;
    int out = 0;

    while(do_program == 1) {
        printf("Enter function:\n");
        scanf("%s", string_console);
        if (strcmp("--start", string_console) == 0) {
            if (in == 1 && out == 1) {
                printf("%s %s %d %d\n", input_file, output_dir, max_iter, dump_freq);
                fin = get_input(input);
                program(fin, max_iter, dump_freq);
            } else if (in == 0) {
                printf("Need input_file file\n");
            } else {
                printf("Need output_dir directory\n");
            }
        }
        if (strcmp("--input", string_console) == 0) {
            printf("input_file:\n");
            scanf("%s", input_file);
            input = input_file;
            printf("good\n");
            in = 1;
        }
        if (strcmp("--output", string_console) == 0) {
            printf("output_dir:\n");
            scanf("%s", output_dir);
            dir_file = output_dir;
            printf("good\n");
            out = 1;
        }
        if (strcmp("--max_iter", string_console) == 0) {
            printf("max_inter:\n");
            scanf("%d", &max_iter);
        }
        if (strcmp("--dump_freq", string_console) == 0) {
            printf("dump_freq:\n");
            scanf("%d", &dump_freq);
        }
        if (strcmp("--end", string_console) == 0) {
            do_program = 0;
        }

        if (strcmp("--write", string_console) == 0) {
            write = 1;
        }
    }
    


    /*

    while(do_program == 1) {
        scanf("%s %s", &string, &input);
        printf("%s %s\n", string, input);

        if (strcmp(string, "--input") == 0) {
            fin = get_input(input);
            printf("good input\n");
            in_file_yes = 1;
        }
        if (strcmp(string, "--output") == 0) {
            output_dir = input;
            printf("good output\n");
            out_file_yes = 1;
        }
        if (strcmp(string, "--max_iter") == 0) {

        }
        if (strcmp(string, "--dump_freq") == 0) {

        }
        if (strcmp(string, "--start") == 0) {
            if (in_file_yes == 1) {
                program(fin, output_dir, max_iter, dump_freq);
            }
        }
        if (strcmp(string, "--end") == 0) {
            do_program = 0;
        }
    }
     */

    return 0;
}


// get_input();
// get_output();
// get_bmp();
// iteration();
// write_bmp();
