def insert_before_all_occurrences_same_row(file_path, search_string, insert_string):
    with open(file_path, 'r') as file:
        content = file.read()

    occurrences = [i for i in range(len(content)) if content.startswith(search_string, i)]

    if occurrences:
        new_content = ""
        start = 0
        for index in occurrences:
            new_content += content[start:index] + insert_string
            start = index
        new_content += content[start:]

        with open(file_path, 'w') as file:
            file.write(new_content)
    else:
        print("Search string not found in the file.")

# Usage example
file_path = 'testfil.txt'
search_string = 'tjabbatjena'
insert_string = 'hejsan svejsan, '

insert_before_all_occurrences_same_row(file_path, search_string, insert_string)