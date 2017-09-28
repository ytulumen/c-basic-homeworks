/*##########################################################################*/
/*                                                                          */
/* HW08_2.c                                                                 */
/* ---------                                                                */
/* Created on 06/05/2015 by Evren Cifci                                     */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*    Sample solution for part2 of hw8                                      */
/*    Takes some appointment requests and people information, accepts the   */
/*    first request for a specific time and rejects all others for that time*/
/*    adds the person's information to the appointment and outputs all      */
/*    information about accepted appointments sorted wrt the date.          */
/*                                                                          */
/* Inputs                                                                   */
/* ------                                                                   */
/* People.txt: Text file holding information about recorded people          */
/* AppointmentReqs.txt: Text file holding information about appointment     */
/*                      requests                                            */
/*                                                                          */
/* Outputs                                                                  */
/* -------                                                                  */
/* Appointments.txt: Text file holding information about accepted           */
/*                   appointments                                           */
/*                                                                          */
/* Notes                                                                    */
/* -----                                                                    */
/* This is a demo files. Usually, the text with in the prolog is more       */
/* verbose.                                                                 */
/*                                                                          */
/* References                                                               */
/* ----------                                                               */
/* (If any)                                                                 */
/*                                                                          */
/*##########################################################################*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*exit*/
#include <math.h> /*pow*/

#define DEBUG

#define SIZE_ID_FIRST_HALF 6
#define SIZE_ID_SECOND_HALF 5
#define SIZE_ID (SIZE_ID_FIRST_HALF + SIZE_ID_SECOND_HALF)
#define MAX_NAME_LENGTH 30
#define MAX_SURNAME_LENGTH 30
#define MAX_FILE_NAME_LENGTH 50
#define MAX_LINE_LENGTH_PEOPLE (MAX_NAME_LENGTH + MAX_SURNAME_LENGTH + SIZE_ID + 5)
#define MAX_LINE_LENGTH_APPO (SIZE_ID + 19)

/*Used to temporarily indicate that the appointment is rejected (first_half of the TC_ID of the people of the appo).
So marked appointments will be deleted later*/
#define REJECTED_APPOINTMENT_CODE -1


const char* PEOPLE_F_NAME = "People.txt";
const char* APPOINTMENT_REQ_F_NAME = "AppointmentReqs.txt";
const char* APPOINTMENT_F_NAME = "Appointments.txt";

typedef enum {MALE, FEMALE} Gender_t;
typedef enum {JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER} Months_t;
typedef enum {FALSE=0, TRUE}  Bool_t;
typedef enum {ERROR_FREE = 0, ID_NOT_NUMERIC, BAD_LINE_FORMAT, MAX_STRING_LENGTH_EXCEEDED_IN_FILE, BAD_GENDER_INDICATOR,
              FILE_NOT_FOUND, BAD_DATE_FORMAT, BAD_TIME_FORMAT, INVALID_TIME, FILE_WRITE_ERROR, PEOPLE_NOT_FOUND} Error_t;

/*Holds TC Id number of a person*/
typedef struct
{
    int first_half;
    int second_half;
} TCId_no_t;

/*Holds all information about a person*/
typedef struct
{
    TCId_no_t id_no;
    char name[30];
    char surname[30];
    Gender_t gender;
} People_t;

/*Holds time information*/
typedef struct
{
    int hour;
    int minute;
} Time_t;

/*Holds a date information including time*/
typedef struct
{
    int year;
    Months_t month;
    int day;
    Time_t time;
} Date_t;

/*Holds all information about an appointment*/
typedef struct
{
    People_t people;
    Date_t date;
} Appointment_t;

/*Holds some existence information about an error*/
typedef struct
{
    Error_t error_type; /*type of the error*/

    /*Optional error parameters: Only some of the following variables has valid
    /*  values for a specific type error*/
    char const *file_name; /*valid in input file format errors only, not that allocation not given*/
    int line_number; /*valid in some file format errors only*/
    TCId_no_t const *id; /*valid in PEOPLE_NOT_FOUND error only*/
} Error_info_t;

/*######################################################################################*/
/*TCId_no_t get_id(const char* id_arr, Error_t* error_case)                             */
/*-----------------------                                                               */
/*  id_arr :character array from which id will be obtained                              */
/*  error_case: health information                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  obtained TC id                                                                      */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Obtains a TC id from the first token of a string                                      */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message in case of a bad string format      */
/*######################################################################################*/
TCId_no_t get_id(const char* id_arr, Error_t* error_case);

/*######################################################################################*/
/*People_t get_person(const char* line, Error_t* error_case)                            */
/*-----------------------                                                               */
/*  line: a string representing a line in a text file in which a People_t record exists */
/*  error_case: health information                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  Obtained People                                                                     */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Obtains a People object from given string                                             */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message in case of a bad string format      */
/*######################################################################################*/
People_t get_person(const char* line, Error_t* error_case);

/*######################################################################################*/
/*int get_people(const char *file_name, People_t people[], int max_size)                */
/*-----------------------                                                               */
/*  file_name: name of the file                                                         */
/*  people: (output) array to be filled                                                 */
/*  max_size: maximum size of the array                                                 */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  Size of the array                                                                   */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Obtains an array of people from given text file                                       */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message if:                                 */
/*       a. File not found                                                              */
/*       b. Format error/data invalidity exists in the file                             */
/*       c. There exists more than max_size people record in the file                   */
/*######################################################################################*/
int get_people(const char *file_name, People_t people[], int max_size);

/*######################################################################################*/
/*Appointment_t get_appointment(const char* line, Error_t* error_case);                 */
/*-----------------------                                                               */
/*  line: a string representing a line in a text file in which a record exists          */
/*  error_case: health information                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  Obtained Appointment request                                                        */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Obtains an Appointment_t object from given string                                     */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message in case of a bad string format      */
/*######################################################################################*/
Appointment_t get_appointment(const char* line, Error_t* error_case);

/*######################################################################################*/
/*int get_appointments(const char *file_name, Appointment_t appointments[], int max_size)*/
/*-----------------------                                                               */
/*  file_name: name of the file                                                         */
/*  appointments: (output) array to be filled                                           */
/*  max_size: maximum size of the array                                                 */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  Size of the array                                                                   */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Obtains an array of appointments from given text file                                 */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message if:                                 */
/*       a. File not found                                                              */
/*       b. Format error/data invalidity exists in the file                             */
/*       c. There exists more than max_size record in the file                          */
/*  2. Empty strings and FEMALE gender are assigned to name, surname and gender fields  */
/*      of Appointment_t objects in the array                                           */
/*######################################################################################*/
int get_appointments(const char *file_name, Appointment_t appointments[], int max_size);

/*######################################################################################*/
/*void write_people_t(const People_t* people, FILE* stream)                             */
/*-----------------------                                                               */
/*  people: People to be written                                                        */
/*  stream: stream in which people will be written                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Writes the attributes of a People_t object to a given stream                          */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message in the case of an error             */
/*######################################################################################*/
void write_people_t(const People_t* people, FILE* stream);

/*######################################################################################*/
/*void print_people(const People_t people[], int size)                                  */
/*-----------------------                                                               */
/*  people: Array of People_t to be written                                             */
/*  size: size of the people array                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Writes the attributes of an array of People_t object to console                       */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Code written for testing                                                         */
/*######################################################################################*/
void print_people(const People_t people[], int size);

/*######################################################################################*/
/*void write_appointment(FILE* file, const Appointment_t* appointment)                  */
/*-----------------------                                                               */
/*  file: file in which the appointment will be written                                 */
/*  appointment: Appointment to be written                                              */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Writes the attributes of an Appointment_t object to a given stream                    */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message in the case of an error             */
/*######################################################################################*/
void write_appointment(FILE* file, const Appointment_t* appointment);

/*######################################################################################*/
/*void write_appointments(const char *file_name, Appointment_t appointments[], int size)*/
/*-----------------------                                                               */
/*  file_name: Name of the file in which appointments are written                       */
/*  appointments: Array of Appointment_t to be written                                  */
/*  size: size of the array                                                             */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Writes the attributes of an array of Appointment_t objects to a text file             */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
void write_appointments(const char *file_name, Appointment_t appointments[], int size);

/*######################################################################################*/
/*void write_names(Appointment_t appointments[], int size_app, const People_t people[], */
/*  int size_people)                                                                    */
/*-----------------------                                                               */
/*  appointments: Array of Appointment_t objects, personal info of which will be written*/
/*  size_appo: size of the appointment array                                            */
/*  people: Array of People_t objects, from where personal info are extracted           */
/*  size_people: size of the people array                                               */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Fills the name, surname and gender fields of people of appointments in the array      */
/*  obtained from people array with tc id search                                        */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message if no people record found for any   */
/*      appointment                                                                     */
/*######################################################################################*/
void write_names(Appointment_t appointments[], int size_app, const People_t people[], int size_people);

/*######################################################################################*/
/*int check_appointments(Appointment_t appointments[], int size)                        */
/*-----------------------                                                               */
/*  appointments: array in which appointment dates are examined                         */
/*  size: size of the array                                                             */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  size of the new array                                                               */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Checks the appointments in an array and deletes all appointments having an identical  */
/*  date with a another appointment with a lower index                                  */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
int check_appointments(Appointment_t appointments[], int size);

/*######################################################################################*/
/*void sort_appointments(Appointment_t appointments[], int size)                        */
/*-----------------------                                                               */
/*  appointments: array which will be sort                                              */
/*  size: size of the array                                                             */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                           */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Sorts the appointments in an array with respect to their date.                        */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
void sort_appointments(Appointment_t appointments[], int size);

/*######################################################################################*/
/*Bool_t is_same_people(const People_t* people1, const People_t* people2)               */
/*-----------------------                                                               */
/*  people1: First people to be compared                                                */
/*  people2: Second people to be compared                                               */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  TRUE/FALSE indicating whether they are the same people                              */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Compares 2 people objects and decides if they represent the same people               */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
Bool_t is_same_people(const People_t* people1, const People_t* people2);

/*######################################################################################*/
/*Bool_t is_at_the_same_time(const Date_t* date1, const Date_t* date2)                  */
/*-----------------------                                                               */
/*  date1: First date to be compared                                                    */
/*  date2: Second date to be compared                                                   */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  TRUE/FALSE indicating whether they represent the same date                          */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Compares 2 date_t objects and decides if they represent the same date                 */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
Bool_t is_at_the_same_time(const Date_t* date1, const Date_t* date2);

/*######################################################################################*/
/*Bool_t is_date_earlier(const Date_t* date1, const Date_t* date2)                      */
/*-----------------------                                                               */
/*  date1: First date to be compared                                                    */
/*  date2: Second date to be compared                                                   */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  TRUE/FALSE indicating whether the 2nd date_t object represents an earlier date      */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Compares 2 date_t objects and decides if the 2nd date_t object represents an earlier  */
/*  date than the 1st date                                                              */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*######################################################################################*/
Bool_t is_date_earlier(const Date_t* date1, const Date_t* date2);

/*######################################################################################*/
/*int ch_arr2int(const char* char_arr, int size, Error_t* error_case)                   */
/*-----------------------                                                               */
/*  arr :character array to be converted                                                */
/*  size:size of the array                                                              */
/*  error_case: health information                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  converted integer                                                                   */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Converts the character array to the integer it represents                             */
/*                                                                                      */
/*Notes                                                                                 */
/*-----                                                                                 */
/*  1. Terminates the program with an error message if the array does not represent     */
/*     an integer                                                                       */
/*######################################################################################*/
int ch_arr2int(const char* char_arr, int size, Error_t* error_case);

/*######################################################################################*/
/*const char* strncpy_until_space(char* dest, const char* source, int max_size,         */
/*      Error_t* error_case)                                                            */
/*-----------------------                                                               */
/*  source: the source string                                                           */
/*  dest: (output)the destination sting                                                 */
/*  max_size: max number of characters to be copied                                     */
/*  error_case: health information                                                      */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  a pointer showing the next character after the space character in source            */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Copies the string in source into the destination until a space character is met or    */
/*  max_size characters are copied                                                      */
/*                                                                                      */
/*Notes                                                                                 */
/*######################################################################################*/
const char* strncpy_until_space(char* dest, const char* source, int max_size, Error_t* error_case);

/*######################################################################################*/
/*void terminate_with_error(Error_info_t* info)                                         */
/*-----------------------                                                               */
/*  info: information about error                                                       */
/*                                                                                      */
/*Return                                                                                */
/*------                                                                                */
/*  void                                                                                */
/*                                                                                      */
/*Description                                                                           */
/*-----------                                                                           */
/*Displays an error message including some information about the occurrence of error    */
/*  and terminates the program with an exit value equal to the error code               */
/*                                                                                      */
/*######################################################################################*/
void terminate_with_error(Error_info_t* info);



int main()
{
    People_t people[20];
    Appointment_t appointments[50];
    int people_c;
    int appo_c;
    int appo_c_accepted;

    people_c = get_people(PEOPLE_F_NAME, people, 20);
    appo_c = get_appointments(APPOINTMENT_REQ_F_NAME, appointments, 50);
    appo_c_accepted = check_appointments(appointments, appo_c);

#ifdef DEBUG
    printf("Number of people: %d\n", people_c);
    print_people(people, people_c);
    printf("\nNumber of all appointments: %d.\n", appo_c);
    printf("Number of accepted appointments: %d.\n", appo_c_accepted);
#endif

    write_names(appointments, appo_c_accepted, people, people_c);
    sort_appointments(appointments, appo_c_accepted);
    write_appointments(APPOINTMENT_F_NAME, appointments, appo_c_accepted);

    return 0;
}


TCId_no_t get_id(const char* id_arr, Error_t* error_case)
{
    TCId_no_t id;

    /*get 1st half*/
    id.first_half = ch_arr2int(id_arr, SIZE_ID_FIRST_HALF, error_case);
    if(*error_case != ERROR_FREE)
        return id; /*error_case already set*/
    else
        id.second_half = ch_arr2int(&id_arr[SIZE_ID_FIRST_HALF], SIZE_ID_SECOND_HALF, error_case);
        /*on error error_case is already set in ch_arr2int()*/

    return id;
}

People_t get_person(const char* line, Error_t* error_case)
{
    People_t person; /*person to be returned*/
    const char* surname_loc;    /*starting address of surname token*/
    const char* gender_loc;     /*starting address of gender token*/
    int i;

    /*get id*/
    person.id_no = get_id(line,  error_case);
    /*check id errors*/
    if(*error_case != ERROR_FREE)
        return person; /*error_case already set*/

    if(line[SIZE_ID] != ' ') /*check format*/
    {
        *error_case = BAD_LINE_FORMAT;
        return person;
    }
    /*get name*/
    surname_loc = strncpy_until_space(person.name, &line[SIZE_ID + 1], MAX_NAME_LENGTH, error_case);

    if(surname_loc) /*not equal to NULL: error-free case*/
        /*get surname*/
        gender_loc = strncpy_until_space(person.surname, surname_loc, MAX_SURNAME_LENGTH,  error_case);

    /*check errors*/
    if(error_case != ERROR_FREE)
        return person; /*there is an error and error_case already assigned*/

    /*get gender*/
    if(*gender_loc == 'M')
        person.gender = MALE;
    else if(*gender_loc == 'F')
        person.gender = FEMALE;
    else
    {
        *error_case = BAD_GENDER_INDICATOR;
        return person;
    }


    /*if gender indicator is not the last character in a line, format of
    that line is erroneous*/
    if(gender_loc[1] != '\0')
    {
        *error_case = BAD_LINE_FORMAT;
        return person;
    }

    return person;
}


int get_people(const char *file_name, People_t people[], int max_size)
{
    FILE* file;     /*file from which array will be obtained*/
    char line[MAX_LINE_LENGTH_PEOPLE]; /*a line of the file*/
    int line_length;    /*length of line*/
    Error_t error_case; /*error type*/
    Error_info_t error; /*error info*/
    int i=0;

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        error.error_type = FILE_NOT_FOUND;
        error.file_name = file_name;/*error.file_name is a ptr not array*/
        terminate_with_error(&error);
    }

    while(fgets(line, MAX_LINE_LENGTH_PEOPLE, file) && (i < max_size))
    {
        line_length = strlen(line);

        if(line_length > 1)
        {
            /*delete new line character*/
            if(line[line_length - 1] == '\n')
                line[line_length - 1] = '\0';
            people[i] = get_person(line, &error_case);
            i++;

            /*check errors*/
            if(error_case != ERROR_FREE)
            {
                error.error_type = error_case;
                error.file_name = file_name;
                error.line_number = i;
                terminate_with_error(&error);
            }

        }

    }

    fclose(file);
    return i;
}


Appointment_t get_appointment(const char* line, Error_t* error_case)
{
    Appointment_t appo; /*appointment to be returned*/
    const char* current_pos;    /*current position on line*/
    int month;  /*month of the returned appointment's date*/
    int day;    /*day of the returned appointment's date*/
    char temp;

    /*get id*/
    appo.people.id_no = get_id(line,  error_case);
    /*check id errors*/
    if(*error_case != ERROR_FREE)
        return appo; /*error_case already set*/

    if(line[SIZE_ID] != ' ') /*check format*/
    {
        *error_case = BAD_LINE_FORMAT;
        return appo;
    }
    /*assign empty strings to name and surname for easy debugging*/
    appo.people.name[0] = '\0';
    appo.people.surname[0] = '\0';
    appo.people.gender = FEMALE;

    /*get year*/
    current_pos = &line[SIZE_ID + 1];
    appo.date.year = ch_arr2int(current_pos, 4, error_case);
    current_pos = &current_pos[4];

     if(*current_pos != ' ') /*check format*/
    {
        *error_case = BAD_LINE_FORMAT;
        return appo;
    }

    current_pos = &current_pos[1];

    /*get month*/
    month = *current_pos - '0';
    current_pos = &current_pos[1];
    temp = *current_pos;
    if(temp != ' ')
    {
        month = month*10 + ((int)temp - '0');
        current_pos = &current_pos[1];
        temp = *current_pos;
        if(temp != ' ')
        {
            *error_case = BAD_DATE_FORMAT;
            return appo;
        }
    }
    if((month < 1) || (month > 12))
    {
        *error_case = BAD_DATE_FORMAT;
        return appo;
    }
    appo.date.month = (Months_t)month;
    current_pos = &current_pos[1];

    /*get day*/
    day = *current_pos - '0';
    current_pos = &current_pos[1];
    temp = *current_pos;
    if(temp != ' ')
    {
        day = day*10 + ((int)temp - '0');
        current_pos = &current_pos[1];
        temp = *current_pos;
        if(temp != ' ')
        {
            *error_case = BAD_DATE_FORMAT;
            return appo;
        }
    }
    if((day < 1) || (day > 31))
    {
        *error_case = BAD_DATE_FORMAT;
        return appo;
    }
    appo.date.day = day;
    current_pos = &current_pos[1];

    /*get time*/
    appo.date.time.hour = ch_arr2int(current_pos, 2, error_case);
    if(*error_case != ERROR_FREE)
        return appo;
    else
    {
        current_pos = &current_pos[2];
        if(*current_pos != ':')
        {
            *error_case = BAD_TIME_FORMAT;
            return appo;
        }
        current_pos = &current_pos[1];
        appo.date.time.minute = ch_arr2int(current_pos, 2, error_case);
    }

    /*check time validity*/
    if((appo.date.time.hour > 24) || (appo.date.time.hour < 0) || ((appo.date.time.minute != 0) && (appo.date.time.minute != 30)))
        *error_case = INVALID_TIME;


    return appo;
}


int get_appointments(const char *file_name, Appointment_t appointments[], int max_size)
{

    FILE* file; /*file from which array will be obtained*/
    char line[MAX_LINE_LENGTH_APPO];    /*a line of the file*/
    int line_length;    /*length of line*/
    Error_t error_case; /*error type*/
    Error_info_t error; /*error info*/
    int i=0;

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        error.error_type = FILE_NOT_FOUND;
        error.file_name = file_name; /*error.file_name is a ptr not array*/
        terminate_with_error(&error);
    }

     while(fgets(line, MAX_LINE_LENGTH_APPO, file) && (i < max_size))
    {
        line_length = strlen(line);

        if(line_length > 1)
        {
            /*delete new line character*/
            if(line[line_length - 1] == '\n')
                line[line_length - 1] = '\0';
            appointments[i] = get_appointment(line, &error_case);
            i++;

            /*check errors*/
            if(error_case != ERROR_FREE)
            {
                error.error_type = error_case;
                error.file_name = file_name;
                error.line_number = i;
                terminate_with_error(&error);
            }

        }

    }

    fclose(file);
    return i;
}


void write_appointment(FILE* stream, const Appointment_t* appointment)
{
    /*write date*/
    fprintf(stream, "%d %d %d %02d:%02d ", appointment->date.year, appointment->date.month, appointment->date.day, appointment->date.time.hour, appointment->date.time.minute);
    /*write people*/
    write_people_t(&appointment->people, stream); /*new line character added in write_people_t()*/
}


void write_appointments(const char *file_name, Appointment_t appointments[], int size)
{
    FILE* file; /*file in which appointment records exist*/
    Error_info_t error; /*health info*/
    int i;

    file = fopen(file_name, "w");
    if(file==NULL)
    {
        error.error_type = FILE_WRITE_ERROR;
        error.file_name = file_name;
        terminate_with_error(&error);
    }

    for(i=0; i<size; ++i)
        write_appointment(file, &appointments[i]);

    fclose(file);
}

void write_names(Appointment_t appointments[], int size_app, const People_t people[], int size_people)
{
    Error_info_t error; /*health info*/
    Bool_t person_found;/*person record for an appointment is found in people array*/
    int i, j;

    for(i=0; i<size_app; ++i)
    {
        person_found = FALSE;
        for(j=0; j<size_people; ++j)
        {
            if((int)is_same_people(&appointments[i].people, &people[j]))
            {
                strcpy(appointments[i].people.name, people[j].name);
                strcpy(appointments[i].people.surname, people[j].surname);
                appointments[i].people.gender = people[j].gender;
                person_found = TRUE;
                break;
            }
        }
        
        /*check if any people record exists for the appointment*/
        if(person_found == FALSE)
        {
            error.error_type = PEOPLE_NOT_FOUND;
            error.id = &(appointments[i].people.id_no);
            terminate_with_error(&error);
        }
    }
}


int check_appointments(Appointment_t appointments[], int size)
{
    int new_index=0;/*new index for the current appointment - used in deletion*/
    int i, j;
    
    /*If more than one appointment requests exists for the same time, */
    /*reject all of these reqs exept the first one by deleting them as follows:*/
    /*  1. Mark them as to be deleted*/
    /*  2. Delete them by shifting the other elements of the array*/
    
    
    /*1. Check all requests and mark those that should be deleted*/
    for(i=0; i<size; ++i)
        for(j=i+1; j<size; ++j)
            if((int)is_at_the_same_time(&appointments[i].date, &appointments[j].date))
                /*mark the last req as to be deleted*/
                appointments[j].people.id_no.first_half = REJECTED_APPOINTMENT_CODE;
    
    /*2. Delete the marked reqs*/
    for(i=0; i<size; ++i)
        if(appointments[i].people.id_no.first_half != REJECTED_APPOINTMENT_CODE)
        {
            /*Accept request: Copy*/
            appointments[new_index] = appointments[i];
            new_index++;
        }
        /*Else, delete by not copying*/
    
        
    return new_index;
}

void sort_appointments(Appointment_t appointments[], int size)
{
    int i,j;
    Appointment_t temp;
    
    for(i=0; i<size-1; ++i)
        for(j=i+1; j<size; ++j)
            if(is_date_earlier(&appointments[j].date, &appointments[i].date))
            {
                /*Swap*/
                temp = appointments[i];
                appointments[i] = appointments[j];
                appointments[j] = temp;
            }
}


int ch_arr2int(const char* ch_arr, int size, Error_t* error_case)
{
    int digit;  /*digit the current character represents*/
    int number=0;   /*number to be returned*/
    int i;

    *error_case = ERROR_FREE;

    for(i=0; i<size; ++i)
    {
        digit = ch_arr[i] - '0';
        if((digit<0) || digit>9)
        {
            /*not a digit: ch_arr is not numeric, return to terminate abnormally*/
            *error_case = ID_NOT_NUMERIC;
            return -1;
        }
        number = 10*number + digit;
    }

    return number;
}


const char* strncpy_until_space(char* dest, const char* source, int max_size, Error_t* error_case)
{
    int i=0;

    *error_case = ERROR_FREE;/*so far we have no errors*/

    /*check validity and copy*/
    while(source[i] != ' ')
    {
        /*check validity*/
        if(i >= max_size)
        {
            *error_case = MAX_STRING_LENGTH_EXCEEDED_IN_FILE;
            return NULL;
        }
        if(source[i] == '\0')
        {
            *error_case = BAD_LINE_FORMAT;
            return NULL;
        }

        /*copy*/
        dest[i] = source[i];
        ++i;
    }

    /*terminate destination*/
    dest[i] = '\0';

    return &source[i+1];
}

void write_people_t(const People_t* people, FILE* stream)
{
    int i;
    
    /*write TC_ID*/
    /*First digit of TC ID cannot be 0, so first 6 digits can be print directly*/
    fprintf(stream, "%d", people->id_no.first_half);
    /*Second Part may start with 0 so id_no.second_half may have less than SIZE_ID_SECOND_HALF digits*/
    for(i=SIZE_ID_SECOND_HALF-1; i>=0; --i)
        fprintf(stream, "%d", (people->id_no.second_half / (int)pow(10, i)) % 10);
    /*Alternatively:
    fprintf(stream, "ID:\t %d%05d\n", people->id_no.first_half, people->id_no.second_half);*/

    /*Write name and surname*/
    fprintf(stream, " %s %s", people->name, people->surname);

    /*Write Gender*/
    if(people->gender == 'M')
        fprintf(stream, " M\n");
    else
        fprintf(stream, " F\n");
}

void print_people(const People_t people[], int size)
{
    int i;

    for(i=0; i<size; ++i)
    {
        printf("-----------------------------people[%d]---------------------\n\n", i);
        write_people_t(&people[i], stdout);
    }
    printf("------------------------------------------------------------\n");
}

Bool_t is_same_people(const People_t* people1, const People_t* people2)
{
    return (Bool_t)((people1->id_no.first_half == people2->id_no.first_half) && (people1->id_no.second_half == people2->id_no.second_half));
}

Bool_t is_at_the_same_time(const Date_t* date1, const Date_t* date2)
{
    return (Bool_t)((date1->year == date2->year) && (date1->month == date2->month) && (date1->day == date2->day) && (date1->time.hour == date2->time.hour) && (date1->time.minute == date2->time.minute));
}

Bool_t is_date_earlier(const Date_t* date1, const Date_t* date2)
{
    if(date1->year > date2->year)
        return FALSE;
    else if(date1->year < date2->year)
        return TRUE;
    else
    {
        /*Same year: first check month*/
        if(date1->month > date2->month)
            return FALSE;
        else if(date1->month < date2->month)
            return TRUE;
        else
        {
            /*Same year and month : first check day*/
            if(date1->day > date2->day)
                return FALSE;
            else if(date1->day < date2->day)
                return TRUE;
            else
            {
                /*Same year, month and day: first check hour*/
                if(date1->time.hour > date2->time.hour)
                    return FALSE;
                else if(date1->time.hour < date2->time.hour)
                    return TRUE;
                else
                {
                    /*Same year, month, day and hour: check minute*/
                    if(date1->time.minute < date2->time.minute)
                        return TRUE;
                    else
                        return FALSE;
                }
            }
        }
    }

}

void terminate_with_error(Error_info_t* info)
{
    switch(info->error_type)
    {
        case ID_NOT_NUMERIC:
            printf("\nERROR: ID is not numeric at line %d of file: %s.\n", info->line_number, PEOPLE_F_NAME);
            break;
        case BAD_LINE_FORMAT:
            printf("\nERROR: Bad line format at line %d of file: %s.\n", info->line_number, info->file_name);
            break;
        case MAX_STRING_LENGTH_EXCEEDED_IN_FILE:
            printf("\nERROR: Line length is too large at line %d of file: %s.\n", info->line_number, PEOPLE_F_NAME);
            break;
        case BAD_GENDER_INDICATOR:
            printf("\nERROR: Bad gender indicator at line %d of file: %s.\n", info->line_number, PEOPLE_F_NAME);
            break;
        case FILE_NOT_FOUND:
            printf("\nERROR: File %s not found!!\n", PEOPLE_F_NAME);
            break;
        case BAD_DATE_FORMAT:
            printf("\nERROR: Bad date format at line %d of file: %s.\n", info->line_number, info->file_name);
            break;
        case BAD_TIME_FORMAT:
            printf("\nERROR: Bad time format at line %d of file: %s.\n", info->line_number, info->file_name);
            break;
        case INVALID_TIME:
            printf("\nERROR: Invalid time at line %d of file: %s.\n", info->line_number, info->file_name);
            break;
        case FILE_WRITE_ERROR:
            printf("\nERROR: File write error at file: %s.\n", info->file_name);
            break;
        case PEOPLE_NOT_FOUND:
            printf("\nERROR: People with TC id %d%05d is not found in people file.\n", info->id->first_half, info->id->second_half);
            break;
        default:
            printf("\nUndefined Error\n");

    }

    exit((int)info->error_type);
}
