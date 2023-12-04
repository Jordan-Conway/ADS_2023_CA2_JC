#include "XMLValidator.h"
#include "XMLTagParser.h"
#include "TreeIterator.h"
#include <queue>
#include <set>
#include <list>

std::optional<Tree<Tag>> XMLValidator::validate(std::ifstream& stream)
{
    std::string line;
    std::queue<Tag> tagQueue;
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
    if (tags.front().getTagName() != "root" || tags.front().getTagType() != OPENING)
    {
        return {};
    }

    std::stack<Tag> stack;

    //Add the first tag
    tagQueue.push(tags.front());
    stack.push(tags.front());
    tags.pop_front();

    bool linesRemaining = true;

    //Process the rest of the file
    while (linesRemaining)
    {
        if (stream.peek() == std::ifstream::traits_type::eof())
        {
            linesRemaining = false;
        }

        while (!tags.empty())
        {
            switch (tags.front().getTagType())
            {
                case OPENING:
                {
                    stack.push(tags.front());
                    break;
                }

                case CLOSING:
                {
                    //If tag is now closed
                    if (tags.front().closes(stack.top()))
                    {
                        stack.pop();
                    }
                    //The document is invalid
                    else
                    {
                        return {};
                    }
                    break;
                }
            }

            tagQueue.push(tags.front());
            tags.pop_front();
        }

        std::getline(stream, line);
        tags = tagParser.getTagsFromString(line);
    }

    if (!stack.empty())
    {
        return {};
    }

    if (tagQueue.empty())
    {
        return {};
    }

    Tree<Tag>* tree = new Tree(tagQueue.front());
    TreeIterator<Tag> iter(tree);
    tagQueue.pop();

    std::set<std::string> nodeTags;
    nodeTags.insert("root");
    nodeTags.insert("dir");
    nodeTags.insert("file");

    while (!tagQueue.empty())
    {
        if (tagQueue.front().getTagName() == "name")
        {
            iter.item().setName(tagQueue.front().getContent());
        }

        if (tagQueue.front().getTagName() == "length")
        {
            iter.item().setLength(tagQueue.front().getContent());
        }

        if (tagQueue.front().getTagName() == "type")
        {
            iter.item().setType(tagQueue.front().getContent());
        }

        if (nodeTags.find(tagQueue.front().getTagName()) != nodeTags.end())
        {
            switch (tagQueue.front().getTagType())
            {
                case OPENING:
                {
                    iter.appendChild(tagQueue.front());
                    while (iter.childIter.currentNode->data->getData() != tagQueue.front())
                    {
                        iter.childIter.advance();
                    }
                    iter.down();
                    break;
                }

                case CLOSING:
                {
                    iter.up();
                    break;
                }

                case SELFCLOSING:
                {
                    iter.appendChild(tagQueue.front());
                    while (iter.childIter.currentNode->data->data != tagQueue.front())
                    {
                        iter.childIter.advance();
                    }
                    break;
                }
            }
        }

        tagQueue.pop();
    }

    return *tree;
}
