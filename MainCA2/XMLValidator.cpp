#include "XMLValidator.h"
#include "XMLTagParser.h"
#include "TreeIterator.h"
#include <list>

std::optional<Tree<Tag>> XMLValidator::validate(std::ifstream& stream)
{
    std::string line;
    XMLTagParser tagParser;

    std::list<Tag> tags;

    //Keep trying unti we find a tag or run out of lines to read
    while (tags.empty() && stream.peek() != std::ifstream::traits_type::eof())
    {
        std::getline(stream, line);
        tags = tagParser.getTagsFromString(line);
    }
    
    //We found no tags
    if (tags.empty())
    {
        return {};
    }

    //All XML documents must start with a root node
    if (tags.front() != Tag("root", OPENING))
    {
        return {};
    }

    std::stack<Tag> stack;

    //Add the first tag
    Tree<Tag>* tree = new Tree(tags.front());
    TreeIterator<Tag> iter(tree);
    stack.push(tags.front());
    tags.pop_front();

    //Process the rest of the file
    while (stream.peek() != std::ifstream::traits_type::eof())
    {
        if (!tags.empty())
        {
            switch (tags.front().getTagType())
            {
            case OPENING:
            {
                stack.push(tags.front());
                iter.appendChild(tags.front());
                iter.down();
                tags.pop_front();
                break;
            }

            case CLOSING:
            {
                //If tag is now closed
                if (tags.front().closes(stack.top()))
                {
                    stack.pop();
                    iter.up();
                }
                //The document is invalid
                else
                {
                    delete tree;
                    return {};
                }
                break;
            }

            case SELFCLOSING:
            {
                iter.appendChild(tags.front());
                tags.pop_front();
                break;
            }
            }
        }

        std::getline(stream, line);
        tags = tagParser.getTagsFromString(line);
    }

    return *tree;
}
