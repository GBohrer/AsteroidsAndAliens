# Asteroids And Aliens - Estrutura Analítica do Projeto (EAP)

## 1.0 Projeto do Jogo Asteroids And Aliens

### 1.1 Gerenciamento do Projeto
- **1.1.1 Iniciação do Projeto**
  - 1.1.1.1 Definir conceito e escopo do jogo
  - 1.1.1.2 Identificar Stakeholders
  - 1.1.1.3 Criar termo de abertura TAP
  - 1.1.1.4 Criar Plano de Projeto
- **1.1.2 Planejamento do Projeto**
  - 1.1.2.1 Criar EAP (WBS)
  - 1.1.2.2 Definir ferramentas e tecnologias
  - 1.1.2.3 Cronograma de desenvolvimento
- **1.1.3 Execução do Projeto**
  - 1.1.3.1 Acompanhamento de tarefas
  - 1.1.3.2 Levantamento de funcionalidades adicionadas
  - 1.1.3.3 Controle de mudanças
- **1.1.4 Monitoramento e Controle**
  - 1.1.4.1 Revisão de progresso
  - 1.1.4.2 Controle de escopo e funcionalidades corretas
  - 1.1.4.3 Acompanhamento de custos
- **1.1.5 Encerramento do Projeto**
  - 1.1.5.1 Aprovação da versão final
  - 1.1.5.2 Retrospectiva e lições aprendidas
  - 1.1.5.3 Arquivamento e backup do projeto

---

### 1.2 Design e Requisitos do Jogo
- **1.2.1 Mecânicas de Jogo**
  - 1.2.1.1 Ciclo principal de gameplay
  - 1.2.1.2 Controle de movimentação da nave
  - 1.2.1.3 Sistema de combate da nave
  - 1.2.1.4 Inteligência dos aliens
  - 1.2.1.5 Física de colisão com entidades
  - 1.2.1.6 Sistema de pontuação do jogador
- **1.2.2 Experiência do Jogador**
  - 1.2.2.1 Apresentação no menu inicial
  - 1.2.2.2 Tutorial (opcional)
- **1.2.3 Interface e UX**
  - 1.2.3.1 Identidade visual do jogo
  - 1.2.3.2 Definição de fontes textuais e paleta de cores
  - 1.2.3.3 Design do menu inicial e configurações
  - 1.2.3.4 Design do HUD in-game
  - 1.2.3.5 Definição de sprites das entidades do jogo
- **1.2.4 Validação de Requisitos**
  - 1.2.5.1 Revisão de funcionalidades
  - 1.2.5.2 Aprovação para desenvolvimento

---

### 1.3 Arquitetura e Design Técnico
- **1.3.1 Planejamento da Arquitetura**
  - 1.3.1.1 Estruturação e estudo do framework com Raylib
  - 1.3.1.2 IDE para desenvolvimento em C/C++
  - 1.3.1.3 Design do loop em GameStates
  ***1.3.1.3 Design modular do Entity-Component-System (ECS)***
    - 1.3.1.3.1 Design de Entidade, Componente e Sistema
    - 1.3.1.3.2 Definição das entidades do jogo
    - 1.3.1.3.3 Definição de componentes necessários para o jogo
    - 1.3.1.3.4 Definição de sistemas necessários para o jogo
- **1.3.2 Gerenciamento de Dados**
  - 1.3.2.1 Design do armazenamento de configurações do usuário
  - 1.3.2.2 Sistema de arquivos para o Leaderboard
- **1.3.4 Balanceamento e Progressão**
  - 1.3.4.1 Progressão de dificuldade (scaling de aliens)
  - 1.3.4.2 Progressão do poder do jogador

---

### 1.4 Desenvolvimento
- **1.4.1 Concepção do ECS**
  - 1.4.1.1 Definição de Entidade, Componente e Sistema
  - 1.4.1.2 Core: Gerenciadores Unitários
  - 1.4.1.3 Core: Gerenciador integrador do ECS
  - 1.4.1.3 Definição dos componentes
  - 1.4.1.4 Definição dos sistemas
- **1.4.2 Implementação da Jogabilidade**
  - 1.4.2.1 Sistema para pipeline de renderização de entidades
  - 1.4.2.1 Sistema de movimentação de entidades
  - 1.4.2.2 Sistema do controle de inputs do jogador
  - 1.4.2.3 Sistema de spawn de aliens e asteroides
  - 1.4.2.4 Sistema do pathing de aliens
  - 1.4.2.5 Sistema de colisões entre entidades
  - 1.4.2.6 Sistema de pontuação do jogador
- **1.4.3 Implementação da Interface**
  - 1.4.3.1 Definição de UIObject e seus derivados
  - 1.4.3.2 Funções de criação das telas e GameStates
  - 1.4.3.3 Carregamento de sprites e geração do cenário da fase
- **1.4.5 Otimização e Revisão de Código**
  - 1.4.5.1 Verificação de performance e memória
  - 1.4.5.2 Refatoração de código
  - 1.4.5.3 Correção de bugs

---

### 1.5 Testes
- **1.5.1 Planejamento de Testes**
  - 1.5.1.1 Definição de estratégia de testes
  - 1.5.1.2 Preparação de ferramentas de teste
- **1.5.2 Testes Unitários**
  - 1.5.2.1 Testes em módulos centrais
  - 1.5.2.2 Testes em mecânicas de jogo
- **1.5.3 Testes de Integração**
  - 1.5.3.1 Integração entre sistemas
- **1.5.4 Testes de Sistema**
  - 1.5.4.1 Execuções completas do jogo
  - 1.5.4.2 Testes de stress e performance

---

### 1.6 Lançamento e Publicação
- **1.6.1 Planejamento de Lançamento**
  - 1.6.1.1 Definição de roadmap de versões
  - 1.6.1.2 Escolha de plataforma de distribuição
- **1.6.2 Compilação e Empacotamento**
  - 1.6.2.1 Automatização da build
  - 1.6.2.2 Empacotamento final
- **1.6.3 Publicação**
  - 1.6.3.1 Criação da página na loja Steam
  - 1.6.3.2 Envio e verificação
- **1.6.4 Pós-lançamento**
  - 1.6.4.1 Gerenciamento de patches
  - 1.6.4.2 Atualizações de funcionalidades
  - 1.6.4.3 Correções rápidas (hotfixes)

---

### 1.7 Documentação
- **1.7.1 Documentação Técnica**
  - 1.7.1.1 Arquitetura do motor ECS
  - 1.7.1.2 Comentários e explicações no código
  - 1.7.1.3 Referência de API Steam (se usada)
- **1.7.2 Documentação de Design**
  - 1.7.2.1 Detalhamento das mecânicas
  - 1.7.2.2 Especificações das funcionalidades
  - 1.7.2.3 Compilado de protótipos de concept arts
- **1.7.3 Documentação para o Jogador**
  - 1.7.3.1 Ajuda
  - 1.7.3.2 Manual de controles
