# Flex-Bison Project
## A Flex-Bison project that reads a myHTML file and checks if it's syntactically correct.
myHTML is a markup pseudolanguage that is supposed to follow HTML standards. myHTML is consisted of different elements which are in turn consisted of three parts: a start tag, its content, an end tag.
Start tags contain the name of the element inside <>, while the end tag contains the same element name inside </>, so a start tag looks like <element_name> and an end tag looks like </element_tag>.
The content of each element might be empty, include text or other elements. Elements must be nested correctly and each end tag should match the previous start tag.
