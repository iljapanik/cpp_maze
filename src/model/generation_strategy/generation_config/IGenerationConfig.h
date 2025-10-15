#pragma once


class IGenerationConfig
{
  public:
	IGenerationConfig() = default;
	IGenerationConfig(int rows, int cols)
	{
		m_rows = rows;
		m_cols = cols;
	}
	virtual ~IGenerationConfig() = default;

	int get_rows() const { return m_rows; }
	int get_cols() const { return m_cols; }

  private:
	int m_rows{};
	int m_cols{};
};
