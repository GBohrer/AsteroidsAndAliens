# Plano de Projeto – *Asteroids And Aliens*

## 1. Informações Iniciais

- **Nome do Projeto**: Asteroids And Aliens  
- **Gerente do Projeto**: Gabriel Alves Bohrer  
- **Data de Início**: 23/03/2025  
- **Data de Término**: 22/06/2025  
- **Versão do Documento**: 1.0  
- **Status**: Em andamento  

---

## 2. Objetivo do Projeto

Desenvolver um jogo arcade independente no estilo arcade utilizando C/C++ e a biblioteca Raylib. Foco em utilizar o padrão de arquitetura ECS no back-end do jogo. Com temática de ficção científica, o jogador poderá combater inimigos alienígenas em um ambiente espacial 2D, incorporando uma gameplay simples e rápida de se aprender, centrada no uso de mouse e teclado de um computador desktop. O jogo será uma ferramenta de aprendizado prático em design de jogos, programação e gerenciamento de projetos.

### Objetivos SMART:

- S: Criar um protótipo jogável com pelo menos 3 mecânicas principais: Habilidades de movimentação e combate contra alienígenas; Pontuação ao derrotar inimigos; progressão da dificuldade.

- M: Lançar o MVP com, pelo menos, 80% dos Requisitos.

- A: Usar C++ e Raylib para garantir domínio das ferramentas e desenvolvimento com recursos limitados.

- R: Aprimorar habilidades em design e gerenciamento de projetos, com documentação completa.

- T: Finalizar a versão mínima viável (MVP) até junho de 2025.

---

## 3. Escopo do Projeto
O jogador poderá controlar uma nave espacial, com o poder de atirar lasers para derrotar os alienígenas. Quanto mais alienígenas o jogador derrotar, mais difícil se torna o jogo: mais inimigos aparecerão, mais rápidos e fortes. Quanto um alienígena alcançar a nave espacial, o jogo termina. Quanto mais tempo o jogador permanecer vivo, maior será sua pontuação - que poderá ser salva em um Leaderboard para comparar suas melhores partidas.

### Escopo Incluído
- Desenvolvimento de um jogo 2D em C/C++ com Raylib.
- MVP com os principais sistemas ECS:
  - Movimentação complexa de entidades
  - Aparição (spawn) de inimigos
  - Pontuação do jogador
  - Progressão de dificuldade
  - Colisão entre entidades
- Interface gráfica simples com:
  - Botões e textos
  - Renderização distinta das entidades
  - UI da nave e informações pertinentes
  - Tela com Debug
- Design modular para expansão futura.

### Fora do Escopo
- Coletáveis e Upgrades (PowerUps) para a nave
- SFX
- Mapa com geração procedural (infinito)
- Banco de Dados para Pontuações de outros jogadores
- Multiplayer online.
- Gráficos 3D e efeitos avançados.
- Publicação comercial.

---

## 4. Stakeholders

| Nome / Papel         | Responsabilidades                                                        |
|----------------------|---------------------------------------------------------------------------|
| Gabriel Bohrer – Dev/Game Designer | Programação, design, documentação e gerenciamento do projeto.             |
| ChatGPT (assistente) | Apoio na organização e brainstorming.                        |
| Ferramentas externas | Geradores de arte, bibliotecas C/C++, editores de som e imagem.          |

---

## 5. Cronograma

### Fases do Projeto

| Fase                       | Período             | Atividades Principais                                           |
|----------------------------|---------------------|-----------------------------------------------------------------|
| Iniciação                  | Março/2025          | Definição do escopo, documentos (TAP, WBS, etc)                 |
| Planejamento               | Abril/2025          | Cronograma, plano de comunicação, Arquitetura e Prototipagem/UX |
| Execução (Desenvolvimento) | Abril a junho/2025  | Codificação, testes, validações                                 |
| Monitoramento e Controle   | Abril a junho/2025  | Avaliações semanais, controle de prazos e escopo                |
| Encerramento               | Junho/2025          | Entrega do MVP, documentação final, revisão geral               |

---

## 6. Recursos

### Equipe
- 1 desenvolvedor full-stack independente: Gabriel Bohrer
- Assistência virtual: ChatGPT

### Tecnologia
- Linguagem: C/C++
- Engine: própria com Raylib
- Editor: VSCode
- Controle de Versão: Git
- Arte: Photoshop

### Orçamento
- Baixo custo (sem equipe externa)
- Investimentos apenas em tempo e ferramentas gratuitas

---

## 7. Plano de Comunicação

- **Ferramentas**: GitHub
- **Relatórios**: Documentação textual com Checkpoints de funcionalidades atingidas
---

## 8. Gestão de Riscos

| Risco                              | Impacto | Mitigação                                                  |
|-----------------------------------|---------|------------------------------------------------------------|
| Excesso de escopo                 | Alto    | Limitar funcionalidades no MVP                            |
| Falta de tempo disponível         | Médio   | Trabalhar com cronograma flexível e metas parciais         |
| Complexidade técnica              | Médio   | Usar Raylib e C++ com bibliotecas acessíveis               |
| Desmotivação                     | Médio   | Focar em entregas curtas e recompensadoras    |

---

## 9. Qualidade

- **Critérios de Aceitação**:
  - Protótipo jogável com os sistemas funcionais sem bugs críticos
  - Interface sem bugs críticos
  - Código modular e comentado

- **Métricas de Qualidade**:
  - Testes manuais a cada nova funcionalidade
  - Refatorações contínuas com base em revisões

---

## 10. Plano de Encerramento

- Conclusão da versão MVP
- Organização dos arquivos finais (código, assets, documentação)
- Commits finais no GitHub
- Avaliação pessoal de aprendizado e performance
- Set-up para versões futuras com novo projeto

---

## 11. Assinaturas de Aprovação

| Nome / Papel                   | Assinatura                 |
|-------------------------------|----------------------------|
| Gabriel Alves Bohrer – Gerente/Dev      | Gabriel A. Bohrer |

