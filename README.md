# Line-Editor
Simple line editor like the first editors for files

Write a simple line editor named ‘edit’. The program is started by entering “edit <filename>” at the
command prompt, where “edit” (or “edit.exe”) is the name of the compiled executable and
“<filename>” is the name of either a new file to create or an exis�ng file to edit.

Keep the entire text in a linked list, each line in a separate node.

Starting
When editing a new file, a prompt simply appears along with a line number, allowing the user to start
entering text or commands.

PS> .\edit new_file.tx

1>

If the file being edited exists and contains text, the contents will be read in and displayed with an
additional prompt to allow the user to enter more text or commands.

PS> .\edit existing_file.txt

1>Once upon a time,

2>in a land far, far away.

3>

Commands

Inserting

Inserting text can be as simple as typing at the displayed line prompts. Any text that isn’t a command will
be entered as text.

If text is to be inserted at a line other than the current line prompt, you can enter an insert command I.

If the leter I is entered with a number n following it, then the current line number will move to that line
and allow text to be inserted there.

1>Once upon a time,

2>in a land far, far away.

3>I 1

1> A Fairy Tale

If I is not followed by a number, then insert the text before the current line. Any text previously on that
line will be moved down one line.

1>Once upon a time,

2>in a land far, far away.

3>I

2>a princess lived,


Listing

Once text has been added, you will want to view lines of the document to see the result. The lis�ng
command is L.

If L is not followed by any numbers (or other text), the en�re contents of the linked list is displayed.

4>L

1>Once upon a time,

2>a princess lived,

3>in a land far, far, away

4>

If L is followed by one number, that line alone will be displayed, and the current line will be changed to
the line following that line.

4>L 2

2>a princess lived,

3>

If L is followed by two numbers, then a range of lines will be displayed, and the current line will be
changed to the next line.

4>L 1 2

1>Once upon a time,

2>a princess lived,

3>

Deleting

Once text has been added, you may want to delete lines of the document. The dele�ng command is D.

If D is followed by one number, then that line will be deleted. If the current line is the last line, the
current line number will be updated, otherwise it will remain the same.

2>a princess lived,

3>in a land far, far, away

4>D 2

3>

If D is followed by two numbers, then a range of lines will be deleted.

1>Once upon a time,

2>a princess lived,

3>D 1 2

1>

If D isn’t followed by any number, then the previous line will be deleted.

1>Once upon a time,

2>a princess lived,

3>D

2>

Exiting / Saving

Entering the E command will exit and saving the text in a file. Entering the Q command will exit without
saving the text to a file.
