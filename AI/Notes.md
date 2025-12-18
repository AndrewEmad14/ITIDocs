# What is AI?
    What is artificial intelligence?
    Artificial intelligence is a specialty within computer science that is concerned with creating systems that can replicate human intelligence and problem-solving abilities
# History of AI
    https://www.tableau.com/data-insights/ai/history#definition
# AI VS ML VS DL VS Gen AI
    AI Vs Machine Learning Vs Deep Learning Vs Generative AI

    1 - Artificial Intelligence (AI)
    It is the overarching field focused on creating machines or systems that can perform tasks typically requiring human intelligence, such as reasoning, learning, problem-solving, and language understanding. AI consists of various subfields, including ML, NLP, Robotics, and Computer Vision

    2 - Machine Learning (ML)
    It is a subset of AI that focuses on developing algorithms that enable computers to learn from and make decisions based on data. 

    Instead of being explicitly programmed for every task, ML systems improve their performance as they are exposed to more data. Common applications include spam detection, recommendation systems, and predictive analytics.

    3 - Deep Learning
    It is a specialized subset of ML that utilizes artificial neural networks with multiple layers to model complex patterns in data. 

    Neural networks are computational models inspired by the human brain’s network of neurons. Deep neural networks can automatically discover representations needed for future detection. Use cases include image and speech recognition, NLP, and autonomous vehicles.

    4 - Generative AI
    It refers to AI systems capable of generating new content, such as text, images, music, or code, that resembles the data they were trained on. They rely on the Transformer Architecture.

    Notable generative AI models include GPT for text generation and DALL-E for image creation.

# fine Tuning vs Reterival augmented Generation(RAG)
    Fine-tuning and Retrieval-Augmented Generation (RAG) are two distinct methods for enhancing the performance of large language models, each with its own strengths and use cases.
    Fine-tuning Overview
    FINE TUNING:
        Fine-tuning involves taking a pre-trained model and further training it on a specific dataset relevant to a particular task or domain. This process updates the model's internal weights, making it more adept at handling specialized content or following specific patterns. The knowledge gained through fine-tuning is static and baked into the model, so it does not change unless the model is retrained. This approach is best suited for tasks that require consistent, high-quality performance within a specialized domain and where the model needs to understand nuanced terminology or styles.
    RAG
        RAG, on the other hand, enhances a model by dynamically retrieving information from external databases or knowledge sources in real-time. Instead of changing the model itself, RAG provides the model with up-to-date, context-specific information during inference. This makes RAG ideal for applications that require the most current data, such as customer support or research, where the underlying information changes frequently. The model's responses are informed by the latest data, but its core behavior and style remain unchanged

# LangChain