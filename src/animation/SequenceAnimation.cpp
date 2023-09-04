#include "SequenceAnimation.h"

#include "TextureManager.h"
#include "tinyxml.h"

void SequenceAnimation::Update(float dt)
{
    if(m_repeat || !m_end)
    {
        m_end = false;
        m_current_frame = (SDL_GetTicks() / m_current_sequence.animation_speed) % m_current_sequence.frame_count;
    }

    if(!m_repeat && m_current_frame == (m_current_sequence.frame_count-1))
    {
        m_end = true;
        m_current_frame = (m_current_sequence.frame_count-1);
    }
}

void SequenceAnimation::Draw(int X, int Y, SDL_RendererFlip flip = SDL_FLIP_NONE, float scale_X = 1.0f, float scale_Y = 1.0f)
{
    TextureManager::GetInstance()->Draw(m_current_sequence.texture_id[m_current_frame], X, Y, m_current_sequence.width, m_current_sequence.height, scale_X, scale_Y, 1.0f, flip);
}

void SequenceAnimation::SetCurrentSequence(std::string sequence_id)
{
    if(m_sequence_map.count(sequence_id) > 0)
        m_current_sequence = m_sequence_map[sequence_id];
    else
        std::cout << "The given sequence animation is not matching : " << sequence_id << std::endl;
}

void SequenceAnimation::Parse(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);

    if(xml.Error())
        std::cout << "Failed to load animation file : " << source << std::endl;

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement())
        if(e->Value() == std::string("sequence"))
        {
            Sequence seq;
            std::string seq_id = e->Attribute("id");
            e->Attribute("animation_speed", &seq.animation_speed);
            e->Attribute("frame_count", &seq.frame_count);
            e->Attribute("width", &seq.width);
            e->Attribute("height", &seq.height);
            for(TiXmlElement* frame=e->FirstChildElement(); frame!=nullptr; frame=frame->NextSiblingElement())
                seq.texture_id.push_back(frame->Attribute("texture_id"));
            m_sequence_map[seq_id] = seq;
        }
}
